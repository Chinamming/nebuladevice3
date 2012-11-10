//------------------------------------------------------------------------------
//  editorapplication.cc
//  (C) 2010 xoyojank
//------------------------------------------------------------------------------
#include "stdeditor.h"
#include "editor/app/editorapplication.h"
#include "debugrender/debugrender.h"
#include "debugrender/debugshaperenderer.h"
#include "math/quaternion.h"
#include "input/keyboard.h"
#include "input/gamepad.h"
#include "framecapture/framecapturerendermodule.h"
#include "framecapture/framecaptureprotocol.h"

#include "io/ioserver.h"

//------------------------------------------------------------------------------
namespace Editor
{

//------------------------------------------------------------------------------
namespace App
{
using namespace CoreGraphics;
using namespace Graphics;
using namespace Math;
using namespace Util;
using namespace Resources;
using namespace Timing;
using namespace Debug;
using namespace Input;
using namespace FrameCapture;

//------------------------------------------------------------------------------
EditorApplication::EditorApplication() :
	hParentWindow(NULL),
	avgFPS(0.0f),
	benchmarkmode(false),
	renderDebug(false),
	capturing(false)
{
	this->SetAppTitle("Nebula3 Editor");
	IO::IoServer* ioServer = IO::IoServer::Instance();

	// make sure log directory exists
	ioServer->CreateDirectory("bin:logfiles");
}

//------------------------------------------------------------------------------
EditorApplication::~EditorApplication()
{
	if (this->IsOpen())
	{
		this->Close();
	}
	this->hParentWindow = NULL;
}

//------------------------------------------------------------------------------
bool
EditorApplication::Open()
{
	if (ViewerApplication::Open())
	{
		// setup lights
		matrix44 lightTransform = matrix44::rotationx(n_deg2rad(-45.0f));
		this->globalLight = GlobalLightEntity::Create();
		this->globalLight->SetTransform(lightTransform);
		this->globalLight->SetColor(float4(0.5, 0.5, 0.5f, 1.0f));
		this->globalLight->SetBackLightColor(float4(0.2f, 0.2f, 0.3f, 1.0f));
		this->globalLight->SetAmbientLightColor(float4(0.42f, 0.42f, 0.42f, 1.0f));
		this->globalLight->SetCastShadows(false);
		this->stage->AttachEntity(this->globalLight.cast<GraphicsEntity>());

		// setup models
		this->ground = ModelEntity::Create();
		this->ground->SetResourceId(ResourceId("mdl:examples/dummyground.n3"));
		this->ground->SetTransform(matrix44::translation(0.0f, 0.0f, 0.0f));
		this->stage->AttachEntity(ground.cast<GraphicsEntity>());

		float spacing = 3.0f;
		for (IndexT j = 0; j < 3; ++j)
		{
			for (IndexT i = 0; i < 3; ++i)
			{
				Ptr<ModelEntity> model = ModelEntity::Create();
				float dir = (i % 2 ? -1.0f : 1.0f);
				float x = (i + 1) * spacing * dir - dir * 0.5f * spacing;
				model->SetTransform(matrix44::translation(x, 0.0, 2.0f * spacing * j));
				model->SetResourceId(ResourceId("mdl:examples/tiger.n3"));
				this->stage->AttachEntity(model.cast<GraphicsEntity>());
				 //createStatic  = !createStatic;
				this->models.Append(model);
			}
		}

		// setup frame capture render module
		Ptr<FrameCaptureRenderModule> module = FrameCaptureRenderModule::Create();
		module->Setup();

		// wait for resources to be loaded
		GraphicsInterface::Instance()->WaitForPendingResources();

		GraphicsInterface::Instance()->EnterLockStepMode();

		return true;
	}
	return false;
}

//------------------------------------------------------------------------------
void
EditorApplication::Close()
{
	GraphicsInterface::Instance()->LeaveLockStepMode();

	this->stage->RemoveEntity(this->globalLight.cast<GraphicsEntity>());
	this->stage->RemoveEntity(this->ground.cast<GraphicsEntity>());
	this->globalLight = 0;
	this->ground = 0;

	for (IndexT i = 0; i < this->models.Size(); i++)
	{
		this->stage->RemoveEntity(this->models[i].cast<GraphicsEntity>());
	}
	this->models.Clear();

	FrameCaptureRenderModule::Instance()->Discard();

	ViewerApplication::Close();
}

//------------------------------------------------------------------------------
void
EditorApplication::Update()
{
	n_assert(this->isOpen);

	_start_timer(MainThreadFrameTimeAll);

	// synchronize with the graphics frame, to prevent the game thread
	// to run ahead of the graphics thread
	_start_timer(MainThreadWaitForGraphicsFrame);
	GraphicsInterface::Instance()->GameThreadWaitForFrameSync();
	_stop_timer(MainThreadWaitForGraphicsFrame);

#if __NEBULA3_HTTP__
	// handle any http requests from the HttpServer thread
	this->httpServerProxy->HandlePendingRequests();
#endif

	// process input
	this->inputServer->BeginFrame();
	this->inputServer->OnFrame();
	this->OnProcessInput();

	// update time
	this->UpdateTime();

	// run "game logic"
	this->OnUpdateFrame();

	// send batched graphics messages
	GraphicsInterface::Instance()->FlushBatchedMessages();

	this->inputServer->EndFrame();

	_stop_timer(MainThreadFrameTimeAll);
}

//------------------------------------------------------------------------------
void
EditorApplication::OnConfigureDisplay()
{
	ViewerApplication::OnConfigureDisplay();

	this->display->SetParentWindow(this->hParentWindow);
}

//------------------------------------------------------------------------------
void
EditorApplication::OnUpdateFrame()
{
	// test text rendering
	Timing::Time frameTime = (float)this->GetFrameTime();

	//  avg frames for every 100 frames
	if (this->frameTimes.Size() > 0 || frameTime < 0.08)
	{
		this->frameTimes.Append(frameTime);
	}
	if (this->frameTimes.Size() > 0 && this->frameTimes.Size() % 50 == 0)
	{
		this->avgFPS = 0;
		IndexT i;
		for (i = 0; i < this->frameTimes.Size(); ++i)
		{
			this->avgFPS += this->frameTimes[i];
		}
		this->avgFPS /=  this->frameTimes.Size();
	}
	Util::String fpsTxt;
	if (this->avgFPS > 0)
	{
		fpsTxt.Format("FPS: %.2f", 1 / this->avgFPS);
	}
	else
	{
		fpsTxt = "Wait for measuring average framerate";
	}
	_debug_text(fpsTxt, Math::float2(0.0, 0.0), Math::float4(1, 1, 1, 1));

	_debug_text("Toggle Benchmark with F3!", Math::float2(0.0, 0.025), Math::float4(1, 1, 1, 1));
	ViewerApplication::OnUpdateFrame();
}

//------------------------------------------------------------------------------
void
EditorApplication::OnProcessInput()
{
	const Ptr<Keyboard>& kbd = InputServer::Instance()->GetDefaultKeyboard();
	const Ptr<GamePad>& gamePad = InputServer::Instance()->GetDefaultGamePad(0);

	// enable/disable debug view
	if (kbd->KeyDown(Key::F4))
	{
		// turn on debug rendering        
		Ptr<Debug::RenderDebugView> renderDebugMsg = Debug::RenderDebugView::Create();
		renderDebugMsg->SetThreadId(Threading::Thread::GetMyThreadId());
		renderDebugMsg->SetEnableDebugRendering(!this->renderDebug);
		Graphics::GraphicsInterface::Instance()->SendBatched(renderDebugMsg.cast<Messaging::Message>());
		this->renderDebug = !this->renderDebug;
	}
	else if (kbd->KeyDown(Key::F3))
	{
		this->benchmarkmode = !this->benchmarkmode;
		// reset to start pos
		this->mayaCameraUtil.Reset();
	}
	else if (kbd->KeyDown(Key::F11))
	{
		Ptr<Messaging::Message> msg;
		if (this->capturing)
		{
			Ptr<StopFrameCapture> stopMsg = StopFrameCapture::Create();
			msg = stopMsg.cast<Messaging::Message>();
			this->capturing = false;
		}
		else
		{
			Ptr<StartFrameCapture> startMsg = StartFrameCapture::Create();
			msg = startMsg.cast<Messaging::Message>();
			this->capturing = true;
		}
		Graphics::GraphicsInterface::Instance()->SendBatched(msg);
	}
	else if (kbd->KeyDown(Key::F7))
	{
		Ptr<SaveScreenShot> msg = SaveScreenShot::Create();
		Graphics::GraphicsInterface::Instance()->SendBatched(msg.cast<Messaging::Message>());
	}

	if (this->benchmarkmode)
	{
		// auto rotate
		this->mayaCameraUtil.SetOrbiting(Math::float2(0.02,0));
		this->mayaCameraUtil.SetOrbitButton(true);
		this->mayaCameraUtil.Update();
		this->camera->SetTransform(this->mayaCameraUtil.GetCameraTransform());
	}
	else
	{                                        
		ViewerApplication::OnProcessInput(); 
	}
}

}// App

}// Editor
