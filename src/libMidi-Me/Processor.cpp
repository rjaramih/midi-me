// Includes
#include "Processor.h"
#include "ProcessorFactory.h"
using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

Processor::Processor(const string &type)
: m_type(type)
{
}

Processor::~Processor()
{
	clear();
}


/******************
* Other functions *
******************/

const InputList &Processor::getInputs() const
{
	return m_inputs;
}

size_t Processor::numInputs() const
{
	return m_inputs.size();
}

const OutputList &Processor::getOutputs() const
{
	return m_outputs;
}

size_t Processor::numOutputs()
{
	return m_outputs.size();
}


/**********************
* Protected functions *
**********************/

void Processor::clear()
{
	InputList::iterator input;
	for(input = m_inputs.begin(); input != m_inputs.end(); ++input)
		delete *input;
	m_inputs.clear();

	OutputList::iterator output;
	for(output = m_outputs.begin(); output != m_outputs.end(); ++output)
		delete *output;
	m_outputs.clear();
}

Input *Processor::addInput()
{
	Input *pInput = new Input();
	m_inputs.push_back(pInput);
	pInput->addListener(this);
	return pInput;
}

Output *Processor::addOutput(bool analog)
{
	Output *pOutput = new Output(analog);
	m_outputs.push_back(pOutput);
	return pOutput;
}


/*******************
* ProcessorCreator *
*******************/

ProcessorCreator::ProcessorCreator(const string &type)
: m_type(type)
{
	ProcessorFactory::getInstance().registerCreator(this);
}

ProcessorCreator::~ProcessorCreator()
{
	ProcessorFactory::getInstance().unregisterCreator(this);
}
