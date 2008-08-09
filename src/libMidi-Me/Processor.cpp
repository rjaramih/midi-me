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

const ValueInputSet &Processor::getValueInputs() const
{
	return m_valueInputs;
}

size_t Processor::numValueInputs() const
{
	return m_valueInputs.size();
}

const RangeInputSet &Processor::getRangeInputs() const
{
	return m_rangeInputs;
}

size_t Processor::numRangeInputs() const
{
	return m_rangeInputs.size();
}

const ValueOutputSet &Processor::getValueOutputs() const
{
	return m_valueOutputs;
}

size_t Processor::numValueOutputs()
{
	return m_valueOutputs.size();
}

const RangeOutputSet &Processor::getRangeOutputs() const
{
	return m_rangeOutputs;
}

size_t Processor::numRangeOutputs()
{
	return m_rangeOutputs.size();
}


/**********************
* Protected functions *
**********************/

void Processor::clear()
{
	ValueInputSet::iterator vi;
	for(vi = m_valueInputs.begin(); vi != m_valueInputs.end(); ++vi)
		delete *vi;
	m_valueInputs.clear();

	RangeInputSet::iterator ri;
	for(ri = m_rangeInputs.begin(); ri != m_rangeInputs.end(); ++ri)
		delete *ri;
	m_rangeInputs.clear();

	ValueOutputSet::iterator vo;
	for(vo = m_valueOutputs.begin(); vo != m_valueOutputs.end(); ++vo)
		delete *vo;
	m_valueOutputs.clear();

	RangeOutputSet::iterator ro;
	for(ro = m_rangeOutputs.begin(); ro != m_rangeOutputs.end(); ++ro)
		delete *ro;
	m_rangeOutputs.clear();
}

ValueInput *Processor::addValueInput()
{
	ValueInput *pInput = new ValueInput();
	m_valueInputs.insert(pInput);
	return pInput;
}

RangeInput *Processor::addRangeInput()
{
	RangeInput *pInput = new RangeInput();
	m_rangeInputs.insert(pInput);
	return pInput;
}

ValueOutput *Processor::addValueOutput(int value)
{
	ValueOutput *pOutput = new ValueOutput(value);
	m_valueOutputs.insert(pOutput);
	return pOutput;
}

RangeOutput *Processor::addRangeOutput(int minValue, int maxValue)
{
	RangeOutput *pOutput = new RangeOutput(minValue, maxValue);
	m_rangeOutputs.insert(pOutput);
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
