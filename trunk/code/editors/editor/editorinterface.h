#pragma once
//------------------------------------------------------------------------------
/**
    @class Editor::EditorInterface
  
    An interface for .net(WPF) to call into native C++(Nebula3).
	Every command is executed in the way of message handling.

    
    (C) 2011 xoyojank
*/
#include "editor/service.h"
#include "editor/control/hostwindow.h"
#include "editor/core/observable.h"
//------------------------------------------------------------------------------
namespace Editor
{
//------------------------------------------------------------------------------
namespace App
{

class EditorApplication;

}// App

using System::Object;
using System::EventArgs;
using System::Collections::Generic::List;

public ref class EditorInterface : public Editor::Core::Observable
{
	MDeclareSingleton(EditorInterface)
public:
	/// constructor
	EditorInterface();
	/// destructor
	~EditorInterface();

	bool Open(Editor::Control::HostWindow^ wnd);
	void Close();

	bool AttachService(Service^ service);
	void DetachService(Service^ service);

	void Send(Cmd::Command^ cmd);

public:
	property System::Object^ EditingObject
	{
		System::Object^ get()
		{
			return this->editingObject;
		}
		void set(System::Object^ obj)
		{
			this->editingObject = obj;
			this->OnPropertyChanged("EditingObject");
		}
	}

private:
	void OnFrameUpdate(Object^ sender, EventArgs^ e);

private:
	App::EditorApplication* editorApp;
	List<Service^>^ services;
	System::Object^ editingObject;
};

}// Editor
