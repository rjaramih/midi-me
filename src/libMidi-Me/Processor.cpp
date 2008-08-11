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

const InputSet &Processor::getInputs() const
{
	return m_inputs;
}

size_t Processor::numInputs() const
{
	return m_inputs.size();
}

const OutputSet &Processor::getOutputs() const
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
	InputSet::iterator input;
	for(input = m_inputs.begin(); input != m_inputs.end(); ++input)
		delete *input;
	m_inputs.clear();

	OutputSet::iterator output;
	for(output = m_outputs.begin(); output != m_outputs.end(); ++output)
		delete *output;
	m_outputs.clear();
}

Input *Processor::addInput(int minValue, int maxValue, bool inverted)
{
	Input *pInput = new Input(minValue, maxValue, inverted);
	m_inputs.insert(pInput);
	return pInput;
}

Output *Processor::addOutput(int minValue, int maxValue, bool analog)
{
	Output *pOutput = new Output(minValue, maxValue, analog);
	m_outputs.insert(pOutput);
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
