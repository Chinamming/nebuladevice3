#pragma once
//------------------------------------------------------------------------------
/**
    @class Editor::Cmd::Command
  
   Base class of editor commands. 
    
    (C) 2011 xoyojank
*/

//------------------------------------------------------------------------------
namespace Editor
{

//------------------------------------------------------------------------------
namespace Cmd
{

public ref class Command abstract
{
public:
	property bool IsHandled;
public:
	Command()
	{
		this->IsHandled = false;
	}
};

public delegate bool CommandHandler(Command^ cmd);

}// Cmd

}// Editor