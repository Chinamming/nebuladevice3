#pragma once
//------------------------------------------------------------------------------
/**
    @class Editor::EditorInterface
  
    An interface for .net(WPF) to call into native C++(Nebula3).
	Every command is executed in the way of message handling.

    
    (C) 2011 xoyojank
*/
#include "editor/service.h"
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

public ref class EditorInterface
{
	MDeclareSingleton(EditorInterface)
public:
	/// constructor
	EditorInterface(HWND hWnd);
	/// destructor
	~EditorInterface();

	bool AttachService(Service^ service);
	void DetachService(Service^ service);

	void Send(Cmd::Command^ cmd);

private:
	void OnFrameUpdate(Object^ sender, EventArgs^ e);

private:
	App::EditorApplication* editorApp;
	List<Service^>^ services;
};

}// Editor
