//------------------------------------------------------------------------------
//  modeleditor.cc
//  (C) 2010 xoyojank
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "editor/app/modeleditor.h"
#include "editor/app/editorapplication.h"
using namespace System::Windows::Media;
using System::EventHandler;

//------------------------------------------------------------------------------
namespace Editor
{

//------------------------------------------------------------------------------
namespace App
{

//------------------------------------------------------------------------------
ModelEditor::ModelEditor(HWND hWnd)
{
	// start nebula device
	this->editorApp = new EditorApplication();
	this->editorApp->SetParentWindow(hWnd);
	bool result = this->editorApp->Open();
	n_assert2(result, "The Nebula Device is failed to initialize!");

	CompositionTarget::Rendering += gcnew EventHandler(this, &ModelEditor::OnFrameUpdate);
}

//------------------------------------------------------------------------------
ModelEditor::~ModelEditor()
{
	// end nebula device
	this->editorApp->Close();
	delete this->editorApp;
	this->editorApp = NULL;
}

//------------------------------------------------------------------------------
void
ModelEditor::OnFrameUpdate(Object^ sender, EventArgs^ e)
{
	// update
	this->editorApp->Update();
}

}// App

}// Editor
