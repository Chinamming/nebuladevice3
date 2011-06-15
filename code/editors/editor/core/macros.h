#pragma once
//------------------------------------------------------------------------------
/**
    @file	macros.h
  
	Some macro definitions.
    
    (C) 2011 xoyojank
*/
//------------------------------------------------------------------------------
#define MAssert System::Diagnostics::Debug::Assert
//------------------------------------------------------------------------------
#define MDeclareSingleton(type) \
public: \
	static type^ Instance; \
private:

#define MConstructSingleton \
	MAssert(Instance == nullptr); Instance = this;

#define MDestructSingleton \
	MAssert(Instance != nullptr); Instance = nullptr;
//------------------------------------------------------------------------------
