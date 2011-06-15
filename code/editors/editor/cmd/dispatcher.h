#pragma once
//------------------------------------------------------------------------------
/**
    @class Editor::Cmd::Dispatcher

	A dispatcher distributes all the commands to the handlers, which are
	interested in the Command::typeid.
  
    @verbatim
                                    +---------+
                                +-->| Handler |
                               /    +---------+
                +------------+/     +---------+
    --- Cmd --->| Dispatcher |----->| Handler |
                +------------+\     +---------+
                               \    +---------+
                                +-->| Handler |
                                    +---------+
    @endverbatim
 
    
    (C) 2011 xoyojank
*/
#include "editor/cmd/command.h"

//------------------------------------------------------------------------------
namespace Editor
{
//------------------------------------------------------------------------------
namespace Cmd
{
using System::Collections::Generic::Dictionary;

public ref class Dispatcher abstract
{
public:
	Dispatcher();
	virtual ~Dispatcher();

	/// register a handler of specific command type
	void RegisterHandler(System::Type^ type, CommandHandler^ handler);
	/// unregister a specific command handler
	void UnRegisterHandler(System::Type^ type);

	/// try to handle a command, return true if it is handled
	bool HandleCommand(Command^ cmd);

protected:
	Dictionary<System::Type^, CommandHandler^>^ handlerMap;
};

}// Cmd

}// Editor