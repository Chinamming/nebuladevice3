#pragma once
#include "editor/app/modeleditor.h"

//------------------------------------------------------------------------------
namespace Editor
{

//------------------------------------------------------------------------------
namespace App
{
using System::Object;
using System::EventArgs;
class EditorApplication;

public ref class ModelEditor
{
public:
	static ModelEditor^ Instance;

public:
	/// constructor
	ModelEditor(HWND hWnd);
	/// destructor
	~ModelEditor();

private:
	void OnFrameUpdate(Object^ sender, EventArgs^ e);

private:
	EditorApplication* editorApp;
};

}// App

}// Editor
