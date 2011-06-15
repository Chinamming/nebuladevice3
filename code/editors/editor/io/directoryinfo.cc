//------------------------------------------------------------------------------
//  directoryinfo.cc
//  (C) 2010 xoyojank
//------------------------------------------------------------------------------
#include "stdeditor.h"
#include "editor/io/directoryinfo.h"
#include "editor/util/typeconvert.h"
#include "io/ioserver.h"

//------------------------------------------------------------------------------
namespace Editor
{

//------------------------------------------------------------------------------
namespace IO
{
using namespace ::IO;
using namespace Editor::Util;

//------------------------------------------------------------------------------
IEnumerable<DirectoryInfo^>^
DirectoryInfo::SubDirectories::get()
{
	IoServer* ioServer = IoServer::Instance();
	URI dirUri = TypeConvert::ToNativeString(this->DirectoryURI);
	::Util::Array<::Util::String> dirs = ioServer->ListDirectories(dirUri, "*");

	array<DirectoryInfo^>^ dirInfos = gcnew array<DirectoryInfo^>(dirs.Size());
	for (IndexT i = 0; i < dirs.Size(); ++i)
	{
		DirectoryInfo^ dirInfo = gcnew DirectoryInfo();
		dirInfo->DirectoryName = TypeConvert::ToManagedString(dirs[i]);
		dirInfo->DirectoryURI = this->DirectoryURI + "/" + dirInfo->DirectoryName;
		dirInfos[i] = dirInfo;
	}

	return dirInfos;
}

}// IO

}// Editor