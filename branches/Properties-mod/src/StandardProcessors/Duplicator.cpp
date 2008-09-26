// Includes
#include "Duplicator.h"
using namespace MidiMe;

// Statics
string Duplicator::type = "Duplicator";


/******************************
* Constructors and destructor *
******************************/

Duplicator::Duplicator()
: Processor(type)
{
	// Add the input
	Input *pInput = addInput();

	// Add the outputs (2 for now)
	addOutput();
	addOutput();
}

Duplicator::~Duplicator()
{
}


/******************
* Other functions *
******************/


/**********************
* Protected functions *
**********************/

void Duplicator::onValue(Input *pInput, real value)
{
	// Send to all outputs
	OutputSet::iterator it;
	for(it = m_outputs.begin(); it != m_outputs.end(); ++it)
		(*it)->sendValue(value);
}


/******************
* DuplicatorCreator *
******************/

Processor *DuplicatorCreator::createProcessor()
{
	return new Duplicator();
}

void DuplicatorCreator::destroyProcessor(Processor *pProcessor)
{
	assert(pProcessor && pProcessor->getType() == Duplicator::type);
	delete pProcessor;
}
