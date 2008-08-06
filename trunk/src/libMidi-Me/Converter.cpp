// Includes
#include "Converter.h"
using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

Converter::Converter(ConverterManager *pManager)
: m_pManager(pManager)
{
	assert(m_pManager);
}

Converter::~Converter()
{
}


/******************
* Other functions *
******************/


/**********************
* Protected functions *
**********************/
