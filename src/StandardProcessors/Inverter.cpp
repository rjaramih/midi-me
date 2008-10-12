// Includes
#include "Inverter.h"
using namespace MidiMe;

// Statics
string Inverter::type = "Inverter";


/******************************
* Constructors and destructor *
******************************/

Inverter::Inverter()
: Processor(type)
{
	// Add the input
	addInput();

	// Add the output
	addOutput();
}

Inverter::~Inverter()
{
}


/******************
* Other functions *
******************/


/**********************
* Protected functions *
**********************/

void Inverter::onValue(Input *pInput, real value)
{
	// Send the inverted signal to all outputs
	OutputList::iterator it;
	for(it = m_outputs.begin(); it != m_outputs.end(); ++it)
		(*it)->sendValue(1 - value);
}


/******************
* InverterCreator *
******************/

Processor *InverterCreator::createProcessor()
{
	return new Inverter();
}

void InverterCreator::destroyProcessor(Processor *pProcessor)
{
	assert(pProcessor && pProcessor->getType() == Inverter::type);
	delete pProcessor;
}
