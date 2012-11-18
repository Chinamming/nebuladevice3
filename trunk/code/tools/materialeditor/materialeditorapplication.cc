//------------------------------------------------------------------------------
//  shadercompilerapplication.cc
//  (C) 2012 xoyojank
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "materialeditorapplication.h"
#include "system/win32/win32registry.h"

namespace Tools
{
using namespace System;
using namespace Util;
using namespace IO;

int __placeholder = 0;
//------------------------------------------------------------------------------
/**
*/
MaterialEditorApplication::MaterialEditorApplication()
	: application(__placeholder, 0)
{
	this->shaderCompiler = ShaderCompiler::Create();
}

//------------------------------------------------------------------------------
/**
*/
MaterialEditorApplication::~MaterialEditorApplication()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
bool
MaterialEditorApplication::ParseCmdLineArgs()
{
	this->filePattern = this->args.GetString("-shd", "*.xml");
	this->shaderCompiler->SetVerbose(this->args.GetBool("-verbose"));
	return true;
}

//------------------------------------------------------------------------------
/**
*/
void
MaterialEditorApplication::Run()
{
	this->application.exec();
}

//------------------------------------------------------------------------------
bool
MaterialEditorApplication::Open()
{
	if (ConsoleApplication::Open())
	{
		this->mainWindow.setWindowTitle(this->GetAppTitle().AsCharPtr());
		// parse command line args
		if (!this->ParseCmdLineArgs())
		{
			return false;
		}
		// get shaderlib base directory
		URI projDirectory;
		if (Win32Registry::Exists(Win32Registry::CurrentUser, "Software\\RadonLabs\\Toolkit", "project"))
		{
			String str = "file:///";
			str.Append(Win32Registry::ReadString(Win32Registry::CurrentUser, "Software\\RadonLabs\\Toolkit", "project"));
			projDirectory = str;
		}
		else
		{
			projDirectory = "home:";
		}

		// load shader fragments and samplers
		this->shaderCompiler->SetProjectDirectory(projDirectory);
		if (!this->shaderCompiler->LoadFragments())
		{
			this->SetReturnCode(10);
			return false;
		}
		if (!this->shaderCompiler->LoadSamplers())
		{
			this->SetReturnCode(10);
			return false;
		}

		// load shader definitions
		if (!this->shaderCompiler->LoadShaders(this->filePattern))
		{
			this->SetReturnCode(10);
			return false;
		}

		// compile shaders
		if (!this->shaderCompiler->Compile())
		{
			this->SetReturnCode(10);
			return false;
		}
		this->mainWindow.show();
		return true;
	}
	return false;
}

//------------------------------------------------------------------------------
void
MaterialEditorApplication::Close()
{
	ConsoleApplication::Close();
}

} // namespace Tools
