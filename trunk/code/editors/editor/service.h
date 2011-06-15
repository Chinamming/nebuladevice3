#pragma once
//------------------------------------------------------------------------------
/**
    @class Editor::Service
  
    Basic function unit of editor.
	All the function calls are command handling.
    
    (C) 2011 xoyojank
*/

#include "editor/cmd/dispatcher.h"
//------------------------------------------------------------------------------
namespace Editor
{

public ref class Service abstract : public Cmd::Dispatcher
{
public:
	property bool IsAttached;
public:
	Service();
	virtual ~Service();

	/// attach to interface
	virtual bool OnAttach();
	/// detach from interface
	virtual void OnDetach();
	/// frame update
	virtual void OnUpdate();
};

}// Editor