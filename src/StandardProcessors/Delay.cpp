// Includes
#include "Delay.h"
using namespace MidiMe;

#include <Properties/StandardProperties.h>


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

	// Create the properties
	createProperties();
}

Delay::~Delay()
{
	// Destroy the properties
	destroyProperties();
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

void Delay::createProperties()
{
	// Add the properties
	RealProperty::GetFunctor valueGetter = fastdelegate::MakeDelegate(this, &Delay::getDelay);
	RealProperty::SetFunctor valueSetter = fastdelegate::MakeDelegate(this, &Delay::setDelay);
	RealProperty *pDelay = new RealProperty("Delay (s)", valueGetter, valueSetter);
	pDelay->setMax(10.0f);
	addProperty(pDelay);
}

void Delay::destroyProperties()
{
	// Destroy all properties
	const PropertyList &props = getPropertiesList();
	for(PropertyList::const_iterator it = props.begin(); it != props.end(); ++it)
		delete *it;
	clearProperties();
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
