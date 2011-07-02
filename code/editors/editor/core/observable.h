#pragma once
//------------------------------------------------------------------------------
/**
	@class	Editor::Core::Observable
  
	The base object can be edited by the property editor.
    
    (C) 2011 xoyojank
*/
using namespace System::ComponentModel;

//------------------------------------------------------------------------------
namespace Editor
{

//------------------------------------------------------------------------------
namespace Core
{

public ref class Observable : public INotifyPropertyChanged
{
public:
	virtual event PropertyChangedEventHandler^ PropertyChanged;

	virtual void OnPropertyChanged(System::String^ propertyName)
	{
		this->PropertyChanged(this, gcnew PropertyChangedEventArgs(propertyName));
	}
};

}// namesapce Core

}// namesapce Editor