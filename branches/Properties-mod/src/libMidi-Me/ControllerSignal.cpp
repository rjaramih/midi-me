// Includes
#include "ControllerSignal.h"
#include "MidiOutput.h"
#include "Output.h"
using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

ControllerSignal::ControllerSignal(MidiOutput *pMidiOutput)
: m_pMidiOutput(pMidiOutput), m_channel(0), m_controller(0), m_startValue(0), m_endValue(128)
{
}

ControllerSignal::~ControllerSignal()
{
}


/******************
* Other functions *
******************/


/**********************
* Protected functions *
**********************/
void ControllerSignal::onValue(Input *pInput, real value)
{
	assert(pInput == this);
	if(!m_pOutput) return;

	// Map the value
	int diffOutput = m_endValue - m_startValue;
	int outValue = (int) (m_startValue + diffOutput * value);

	m_pMidiOutput->sendControllerMessage(m_channel, m_controller, outValue);
}
