// Includes
#include "Connection.h"
#include "Input.h"
#include "Output.h"
using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

Connection::Connection(Input *pInput, Output *pOutput)
: m_pInput(pInput), m_pOutput(pOutput), m_inverted(false)
{
	assert(m_pInput && m_pOutput);

	// Make connection
	//! @todo Remove previous connections
	m_pInput->setConnection(this);
	m_pOutput->setConnection(this);
}

Connection::~Connection()
{
	m_pInput->setConnection(0);
	m_pOutput->setConnection(0);
}


/******************
* Other functions *
******************/

void Connection::processValue(real value)
{
	// Invert if necessary
	if(m_inverted)
		value = 1 - value;

	m_pInput->processValue(value);
}


/**********************
* Protected functions *
**********************/
