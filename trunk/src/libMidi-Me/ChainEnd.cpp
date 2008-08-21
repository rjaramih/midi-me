// Includes
#include "ChainEnd.h"
using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

ChainEnd::ChainEnd(MidiOutput *pMidi, Input *pInput)
: m_pMidi(pMidi), m_pInput(pInput)
{
	assert(m_pMidi && m_pInput);
}

ChainEnd::~ChainEnd()
{
}


/******************
* Other functions *
******************/


/**********************
* Protected functions *
**********************/
