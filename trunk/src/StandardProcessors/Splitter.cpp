// Includes
#include "Splitter.h"
using namespace MidiMe;

#include <Properties/StandardProperties.h>
#include <libMidi-Me/Midi-MeProperties.h>


// Statics
string Splitter::type = "Splitter";


/******************************
* Constructors and destructor *
******************************/

Splitter::Splitter()
: Processor(type), m_splitValue(0.5), m_deadZone(0), m_prevValue(0)
{
	// Add the input
	m_pInput = addInput();

	// Add the outputs
	m_pOutput1 = addOutput();
	m_pOutput1->setInfo("<");

	m_pOutput2 = addOutput();
	m_pOutput2->setInfo(">=");

	// Create the properties
	createProperties();
}

Splitter::~Splitter()
{
	// Destroy the properties
	destroyProperties();
}


/******************
* Other functions *
******************/


/**********************
* Protected functions 
**********************/

void Splitter::onValue(Input *pInput, real value)
{
	// If in the dead zone, send border value to previous output
	if(value > m_splitValue - m_deadZone && value < m_splitValue + m_deadZone)
	{
		// Send border value to other output if the value crossed the split value
		if(m_prevValue >= m_splitValue + m_deadZone)
			m_pOutput2->sendValue(0);

		else if(m_prevValue <= m_splitValue - m_deadZone)
			m_pOutput1->sendValue(1);

		return;
	}

	if(value < m_splitValue)
	{
		real mappedValue = value / (m_splitValue - m_deadZone);
		m_pOutput1->sendValue(mappedValue);
	}
	else
	{
		real edgeValue = m_splitValue + m_deadZone;
		real mappedValue = (value - edgeValue) / ((real) 1.0 - edgeValue);
		m_pOutput2->sendValue(mappedValue);
	}

	m_prevValue = value;
}

void Splitter::createProperties()
{
	// Add the properties
	InputValueProperty::GetFunctor valueGetter = fastdelegate::MakeDelegate(this, &Splitter::getSplitValue);
	InputValueProperty::SetFunctor valueSetter = fastdelegate::MakeDelegate(this, &Splitter::setSplitValue);
	InputValueProperty *pSplitValue = new InputValueProperty("Split value", valueGetter, valueSetter, m_pInput);
	addProperty(pSplitValue);

	RealProperty::GetFunctor dzGetter = fastdelegate::MakeDelegate(this, &Splitter::getDeadZone);
	RealProperty::SetFunctor dzSetter = fastdelegate::MakeDelegate(this, &Splitter::setDeadZone);
	RealProperty *pDeadZone = new RealProperty("Dead zone", dzGetter, dzSetter);
	addProperty(pDeadZone);

	pDeadZone->setMin(0);
	pDeadZone->setMax(1);
}

void Splitter::destroyProperties()
{
	// Note: We copy this list so we can call clearProperties and inform the listeners
	const PropertyList props = getPropertiesList();
	clearProperties();

	// Destroy all properties
	for(PropertyList::const_iterator it = props.begin(); it != props.end(); ++it)
		delete *it;
}



/******************
* SplitterCreator *
******************/

Processor *SplitterCreator::createProcessor()
{
	return new Splitter();
}

void SplitterCreator::destroyProcessor(Processor *pProcessor)
{
	assert(pProcessor && pProcessor->getType() == Splitter::type);
	delete pProcessor;
}
