// Includes
#include "ClassName.h"
using namespace MidiMe;


/*!
	Get the instance of this singleton class.
	You need to use this function to access the class,
	as the constructor is private.
*/
ClassName &ClassName::getInstance()
{
	static ClassName instance;
	return instance;
}


/******************************
* Constructors and destructor *
******************************/

ClassName::ClassName()
{
}

ClassName::~ClassName()
{
}


/************************
* Get and set functions *
************************/


/******************
* Other functions *
******************/


/**********************
* Protected functions *
**********************/
