// Includes
#include "Connection.h"
using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

Connection::Connection(Input *pInput, Output *pOutput)
: m_pInput(pInput), m_pOutput(pOutput), m_inverted(false)
{
}

Connection::~Connection()
{
}


/******************
* Other functions *
******************/


/**********************
* Protected functions *
**********************/
