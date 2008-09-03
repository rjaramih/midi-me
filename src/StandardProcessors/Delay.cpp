// Includes
#include "Delay.h"
using namespace MidiMe;

// Statics
string Delay::type = "Delay";


/******************************
* Constructors and destructor *
******************************/

Delay::Delay()
: Processor(type), m_delay(0), m_currentTime(0)
{
	// Add the input
	addInput();

	// Add the output
	addOutput();

	// TEMP: Delay for 2 seconds
	setDelay(2.0f);
}

Delay::~Delay()
{
}


/******************
* Other functions *
******************/

void Delay::step(float seconds)
{
	m_currentTime += seconds;

	// The output
	assert(m_outputs.size() == 1);
	Output *pOutput = *m_outputs.begin();

	// Search the values that have to be sent now
	TimeValueMap::iterator it;
	for(it = m_values.begin(); it != m_values.end(); )
	{
		// If we find a value that doesn't have to be sent yet, all next ones won't have to either
		if(it->first + m_delay > m_currentTime)
			break;

		// Send to output
		pOutput->sendValue(it->second);

		// Erase the value from the map
		m_values.erase(it++);
	}

	// We can reset the timer if no values are left
	if(m_values.empty())
		m_currentTime = 0;
}


/**********************
* Protected functions *
**********************/

void Delay::onValue(Input *pInput, real value)
{
	// Note: only one value can be recorded each time step
	m_values[m_currentTime] = value;
}


/******************
* DelayCreator *
******************/

Processor *DelayCreator::createProcessor()
{
	return new Delay();
}

void DelayCreator::destroyProcessor(Processor *pProcessor)
{
	assert(pProcessor && pProcessor->getType() == Delay::type);
	delete pProcessor;
}
