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
: Processor(type), m_splitValue(0.5)
{
	// Add the input
	m_pInput = addInput();

	// Add the outputs
	m_pOutput1 = addOutput();
	m_pOutput2 = addOutput();

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
		real mappedValue = value / m_splitValue;
		m_pOutput1->sendValue(mappedValue);
	}
	else
	{
		real mappedValue = (value - m_splitValue) / ((real) 1.0 - m_splitValue);
		m_pOutput2->sendValue(mappedValue);
	}
}

void Splitter::createProperties()
{
	// Add the properties
	InputValueProperty::GetFunctor valueGetter = fastdelegate::MakeDelegate(this, &Splitter::getSplitValue);
	InputValueProperty::SetFunctor valueSetter = fastdelegate::MakeDelegate(this, &Splitter::setSplitValue);
	InputValueProperty *pSplitValue = new InputValueProperty(this, "Split value", valueGetter, valueSetter, m_pInput);
}

void Splitter::destroyProperties()
{
	// Destroy all properties
	// Note; We make a copy of the list because it will be altered at destruction of the property
	const PropertyList props = getPropertiesList();
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
