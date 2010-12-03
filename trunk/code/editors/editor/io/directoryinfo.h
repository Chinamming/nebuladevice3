#pragma once
//------------------------------------------------------------------------------
/**
    @class Editor::IO::DirectoryInfo
  
	A helper class for iterator file tree.
    
    (C) 2010 xoyojank
*/
using namespace System::Collections::Generic;
//------------------------------------------------------------------------------
namespace Editor
{

//------------------------------------------------------------------------------
namespace IO
{

public ref class DirectoryInfo
{
public:
	property System::String^ DirectoryName;	///< directory name without path
	property System::String^ DirectoryURI;	///< full uri, such as mesh:system

	property IEnumerable<DirectoryInfo^>^ SubDirectories
	{
		IEnumerable<DirectoryInfo^>^ get();
	}

};

}// IO

}// Editor