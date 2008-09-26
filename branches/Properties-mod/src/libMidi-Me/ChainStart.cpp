// Includes
#include "ChainStart.h"
#include "InputDevice.h"
using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

ChainStart::ChainStart(InputDevice *pDevice, unsigned int outputID)
: m_pDevice(pDevice), m_outputID(outputID)
{
	assert(m_pDevice && m_pDevice->outputExists(outputID));
}

ChainStart::~ChainStart()
{
}


/******************
* Other functions *
******************/

Output *ChainStart::getOutput() const
{
	return m_pDevice->getOutput(m_outputID);
}


/**********************
* Protected functions *
**********************/
