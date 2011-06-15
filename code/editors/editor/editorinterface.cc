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
EditorInterface::EditorInterface(HWND hWnd)
{
	MConstructSingleton;
	// start nebula device
	this->editorApp = new EditorApplication();
	this->editorApp->SetParentWindow(hWnd);
	bool result = this->editorApp->Open();
	MAssert(result, "The Nebula Device is failed to initialize!");

	CompositionTarget::Rendering += gcnew EventHandler(this, &EditorInterface::OnFrameUpdate);

	this->services = gcnew List<Service^>();
	this->AttachService(gcnew Debug::Log());
}

//------------------------------------------------------------------------------
EditorInterface::~EditorInterface()
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

}// Editor
