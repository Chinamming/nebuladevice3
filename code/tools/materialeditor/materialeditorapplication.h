#pragma once
#ifndef TOOLS_SHADERCOMPILERAPPLICATION_H
#define TOOLS_SHADERCOMPILERAPPLICATION_H
//------------------------------------------------------------------------------
/**
    @class Tools::MaterialEditorApplication
    
    Application class for the Nebula3 material editor. This is just a GUI wrapper
    around the class ShaderCompiler.

    (C) 2007 xoyojank
*/
#include "app/consoleapplication.h"
#include "nsc3/shadercompiler.h"
#include "mainwindow.h"
#include <QtGui/QApplication>

//------------------------------------------------------------------------------
namespace Tools
{
class MaterialEditorApplication : public App::ConsoleApplication
{
public:
    /// constructor
    MaterialEditorApplication();
    /// destructor
    ~MaterialEditorApplication();

    /// open the application
    virtual bool Open();
    /// close the application
    virtual void Close();

    /// run the application
    virtual void Run();

private:
    /// parse command line arguments
    bool ParseCmdLineArgs();
    
    Ptr<ShaderCompiler> shaderCompiler;
    Util::String filePattern;
	QApplication application;
	MainWindow mainWindow;
};

} // namespace Tools
//------------------------------------------------------------------------------
#endif