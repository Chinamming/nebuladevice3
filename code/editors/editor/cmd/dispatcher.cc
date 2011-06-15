//------------------------------------------------------------------------------
//  dispatcher.cc
//  (C) 2011 xoyojank
//------------------------------------------------------------------------------
#include "stdeditor.h"
#include "editor/cmd/dispatcher.h"

//------------------------------------------------------------------------------
namespace Editor
{
//------------------------------------------------------------------------------
namespace Cmd
{

//------------------------------------------------------------------------------
Dispatcher::Dispatcher()
{
	this->handlerMap = gcnew Dictionary<System::Type^, CommandHandler^>();
}

//------------------------------------------------------------------------------
Dispatcher::~Dispatcher()
{
	delete this->handlerMap;
}

//------------------------------------------------------------------------------
void
Dispatcher::RegisterHandler(System::Type ^ type, CommandHandler ^ handler)
{
	this->handlerMap->Add(type, handler);
}

//------------------------------------------------------------------------------
void
Dispatcher::UnRegisterHandler(System::Type ^ type)
{
	this->handlerMap->Remove(type);
}

//------------------------------------------------------------------------------
bool
Dispatcher::HandleCommand(Command ^ cmd)
{
	CommandHandler^ handler = nullptr;	
	if (this->handlerMap->TryGetValue(cmd->GetType(), handler))
	{
		if (handler->Invoke(cmd))
		{
			cmd->IsHandled = true;
			return true;
		}
	}
	return false;
}

}// Cmd

}// Editor