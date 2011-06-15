#pragma once
//------------------------------------------------------------------------------
/**
    @class Editor::Debug::Log
  
	Log service for editor.
	Log files are written by Trace's listener.
    
    (C) 2011 xoyojank
*/
#include "editor/service.h"
//------------------------------------------------------------------------------
namespace Editor
{
//------------------------------------------------------------------------------
namespace Debug
{

public ref class Log : public Service
{
public:
	/// attach to interface
	virtual bool OnAttach() override;
	/// detach from interface
	virtual void OnDetach() override;
private:
	System::Diagnostics::TraceListener^ traceListener;
};

}// Debug

}// Editor