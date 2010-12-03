#pragma once
//------------------------------------------------------------------------------
/**
    @class Editor::Util::TypeConvert
  
    a helper class for converting data types.
    
    (C) 2010 xoyojank
*/
#include "util/string.h"
#include "util/array.h"
//------------------------------------------------------------------------------
namespace Editor
{

//------------------------------------------------------------------------------
namespace Util
{

public ref class TypeConvert abstract sealed
{
public:
	/// convert to managed String
	static System::String^ ToManagedString(const ::Util::String& s);
	/// convert to native Util::String
	static ::Util::String ToNativeString(System::String^ s);
};

}// Util

}// Editor