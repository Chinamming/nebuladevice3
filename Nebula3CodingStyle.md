#This is the coding style of nebula3.

# Header Files #
  * use "#pragma once" instead of #define guard
  * inline funtions should be implemented out of the class scope

# Scoping #
  * don't intent the code in a namespace scope
  * don't define global enums, use a struct to pack them
  * don't use global variabals
  * don't use "using namespace" in header files

# Classes #
  * don't use multiple inheritance, especially when the class is a sub-class of RefCounted
  * don't use public member variables

# Naming #
  * use a naming style likes .NetFramework
  * use "this->" to reference member variables and methods
  * use lower case names for global functions
  * macros/enum elements/constant values are defined like "InvalidThreadId", not all in upper cases
  * some agreements: bool isOpen; Array`<bbox>` boxes;

# Comments #
  * place a class comment at the begin of a .h file
  * place a file comment at the begine of a .cc file
  * use "//------" to seperate method definations
  * use one line comment for method declaration, with three slashes
  * use multi-line comment for method defination
  * add "@todo" or "FIXME" key word for further implements

# Other #
  * don't use RTTI of C++, use n3's instead
  * don't use STL and exceptions
  * use smart pointer(Ptr class) instead of C style pointers
  * the return type should be placed in the different line with the method defination