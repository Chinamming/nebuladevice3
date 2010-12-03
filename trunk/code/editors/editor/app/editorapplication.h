#pragma once
//------------------------------------------------------------------------------
/**
    @class Editor::App::EditorApplication

	Editor application used by C++/CLI, need a parent window to display.

    (C) 2010 xoyojank
*/
#pragma unmanaged
#include "apprender/viewerapplication.h"
#include "graphics/spotlightentity.h"
#include "graphics/modelentity.h"
#include "graphics/globallightentity.h"
#include "graphics/pointlightentity.h"
#pragma managed

//------------------------------------------------------------------------------
namespace Editor
{

//------------------------------------------------------------------------------
namespace App
{

class EditorApplication : public ::App::ViewerApplication
{
public:
	/// constructor
	EditorApplication();
	/// destructor
	virtual ~EditorApplication();

	/// set parent window handle, call before Open()
	void SetParentWindow(HWND hWnd);

	/// open the application
	virtual bool Open();
	/// close the application
	virtual void Close();

	/// update the application
	void Update();

private:
	/// process input (called before rendering)
	virtual void OnProcessInput();
	/// called to configure display
	virtual void OnConfigureDisplay();
	/// render current frame
	virtual void OnUpdateFrame();

private:
	HWND hParentWindow;

	Ptr<Graphics::ModelEntity> ground;
	Util::Array<Ptr<Graphics::ModelEntity> > models;
	Ptr<Graphics::GlobalLightEntity> globalLight;
	Util::Array<Timing::Time> frameTimes;
	Timing::Time avgFPS;
	bool benchmarkmode;
	bool renderDebug;
	bool capturing;
};

//------------------------------------------------------------------------------
inline void
EditorApplication::SetParentWindow(HWND hWnd)
{
	this->hParentWindow = hWnd;
}

}// App

}// Editor
