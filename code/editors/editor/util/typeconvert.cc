//------------------------------------------------------------------------------
//  typeconvert.cc
//  (C) 2010 xoyojank
//------------------------------------------------------------------------------
#include "stdeditor.h"
#include "editor/util/typeconvert.h"
//------------------------------------------------------------------------------
namespace Editor
{

//------------------------------------------------------------------------------
namespace Util
{
using namespace System::Runtime::InteropServices;
using System::IntPtr;

//------------------------------------------------------------------------------
System::String^
TypeConvert::ToManagedString(const ::Util::String& s)
{
	return Marshal::PtrToStringAnsi(static_cast<IntPtr>((char*)s.AsCharPtr()));
}

//------------------------------------------------------------------------------
::Util::String
TypeConvert::ToNativeString(System::String^ s)
{
	::Util::String native;
	IntPtr ptr = Marshal::StringToHGlobalAnsi(s);
	const char* charPtr = static_cast<const char*>(ptr.ToPointer());
	native = charPtr;
	Marshal::FreeHGlobal(ptr);
	return native;
}


}// Util

}// Editor