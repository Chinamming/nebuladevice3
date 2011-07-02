//------------------------------------------------------------------------------
//  editorinterface.cc
//  (C) 2010 xoyojank
//------------------------------------------------------------------------------
#include "stdeditor.h"
#include "editor/editorinterface.h"
#include "editor/debug/log.h"
#include "editor/app/editorapplication.h"
using namespace System::Windows::Media;
using System::EventHandler;
using namespace System::Diagnostics;

//------------------------------------------------------------------------------
namespace Editor
{
using namespace App;

//------------------------------------------------------------------------------
EditorInterface::EditorInterface()
{
	MConstructSingleton;
}

//------------------------------------------------------------------------------
EditorInterface::~EditorInterface()
{
	MDestructSingleton;
}

//------------------------------------------------------------------------------
void
EditorInterface::OnFrameUpdate(Object^ sender, EventArgs^ e)
{
	// update
	this->editorApp->Update();

	for each(Service^ service in this->services)
	{
		service->OnUpdate();
	}
}

//------------------------------------------------------------------------------
bool
EditorInterface::AttachService(Service^ service)
{
	if (service->OnAttach())
	{
		this->services->Add(service);
		return true;
	}
	return false;
}

//------------------------------------------------------------------------------
void
EditorInterface::DetachService(Service^ service)
{
	if (this->services->Remove(service))
	{
		service->OnDetach();
	}
}

//------------------------------------------------------------------------------
void
EditorInterface::Send(Cmd::Command^ cmd)
{
	try
	{
		for each(Service^ service in this->services)
		{
			if (service->HandleCommand(cmd))
			{
				return;
			}
		}
	}
	catch (System::Exception^ e)
	{
		Trace::WriteLine(e->Message);
	}
}

//------------------------------------------------------------------------------
bool
EditorInterface::Open(Editor::Control::HostWindow^ wnd)
{
	// start nebula device
	this->editorApp = new EditorApplication();
	this->editorApp->SetParentWindow(wnd->GetParentWnd());
	bool result = this->editorApp->Open();
	if (!result)
	{
		MAssert(result, "The Nebula Device is failed to initialize!");
		return false;
	}

	CompositionTarget::Rendering += gcnew EventHandler(this, &EditorInterface::OnFrameUpdate);

	this->services = gcnew List<Service^>();
	this->AttachService(gcnew Debug::Log());

	return true;
}

//------------------------------------------------------------------------------
void
EditorInterface::Close()
{
	// close services
	for each (Service^ service in this->services)
	{
		service->OnDetach();
	}
	this->services->Clear();
	delete this->services;

	// end nebula device
	this->editorApp->Close();
	delete this->editorApp;
	this->editorApp = NULL;
}

}// Editor
