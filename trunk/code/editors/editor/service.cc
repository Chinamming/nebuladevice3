//------------------------------------------------------------------------------
//  service.cc
//  (C) 2011 xoyojank
//------------------------------------------------------------------------------
#include "stdeditor.h"
#include "editor/service.h"
using namespace System::Diagnostics;

//------------------------------------------------------------------------------
namespace Editor
{

//------------------------------------------------------------------------------
Service::Service()
{
	this->IsAttached = false;
}

//------------------------------------------------------------------------------
Service::~Service()
{
	MAssert(!this->IsAttached);
}

//------------------------------------------------------------------------------
bool
Service::OnAttach()
{
	MAssert(!this->IsAttached);

	this->IsAttached = true;
	return true;
}

//------------------------------------------------------------------------------
void
Service::OnDetach()
{
	MAssert(this->IsAttached);

	this->IsAttached = false;
}

//------------------------------------------------------------------------------
void
Service::OnUpdate()
{
	// overriden in sub classes
}

}// Editor