// Includes
#include "Splitter.h"
using namespace MidiMe;

// Statics
string Splitter::type = "Splitter";


/******************************
* Constructors and destructor *
******************************/

Splitter::Splitter()
: Processor(type), m_splitValue(50)
{
	// Add the input
	Input *pInput = addInput();

	// Add the outputs
	m_pOutput1 = addOutput();
	m_pOutput2 = addOutput();
}

Splitter::~Splitter()
{
}


/******************
* Other functions *
******************/


/**********************
* Protected functions *
**********************/

void Splitter::onValue(Input *pInput, int value)
{
	if(value < m_splitValue)
		m_pOutput1->sendValue(value);
	else
		m_pOutput2->sendValue(value);
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
