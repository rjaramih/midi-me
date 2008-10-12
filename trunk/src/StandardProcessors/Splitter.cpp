// Includes
#include "Splitter.h"
using namespace MidiMe;

#include <libMidi-Me/Midi-MeProperties.h>


// Statics
string Splitter::type = "Splitter";


/******************************
* Constructors and destructor *
******************************/

Splitter::Splitter()
: Processor(type), m_splitValue(0.5), m_prevValue(0)
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
	if(value < m_splitValue)
	{
		// Send border value to other output if the value crossed the split value
		if(m_prevValue >= m_splitValue)
			m_pOutput2->sendValue(0);

		real mappedValue = value / m_splitValue;
		m_pOutput1->sendValue(mappedValue);
	}
	else
	{
		// Send border value to other output if the value crossed the split value
		if(m_prevValue < m_splitValue)
			m_pOutput1->sendValue(1);

		real mappedValue = (value - m_splitValue) / ((real) 1.0 - m_splitValue);
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
