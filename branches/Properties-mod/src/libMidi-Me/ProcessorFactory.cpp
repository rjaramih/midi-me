// Includes
#include "ProcessorFactory.h"
#include "Processor.h"
using namespace MidiMe;


/*!
	Get the instance of this singleton class.
	You need to use this function to access the class,
	as the constructor is private.
*/
ProcessorFactory &ProcessorFactory::getInstance()
{
	static ProcessorFactory instance;
	return instance;
}


/******************************
* Constructors and destructor *
******************************/

ProcessorFactory::ProcessorFactory()
{
}

ProcessorFactory::~ProcessorFactory()
{
}


/***********
* Creators *
***********/

const ProcessorCreatorMap &ProcessorFactory::getAllCreators() const
{
	return m_creators;
}

bool ProcessorFactory::canCreate(const string &type) const
{
	return m_creators.find(type) != m_creators.end();
}

ProcessorCreator *ProcessorFactory::getCreator(const string &type) const
{
	ProcessorCreatorMap::const_iterator it = m_creators.find(type);
	return (it == m_creators.end()) ? 0 : it->second;
}


/*************
* Processors *
*************/

Processor *ProcessorFactory::createProcessor(const string &type)
{
	ProcessorCreator *pCreator = getCreator(type);
	if(!pCreator)
		return 0;

	return pCreator->createProcessor();
}

void ProcessorFactory::destroyProcessor(Processor *pProcessor)
{
	if(!pProcessor)
		return;

	ProcessorCreator *pCreator = getCreator(pProcessor->getType());
	if(!pCreator)
	{
		cerr << "[ProcessorFactory] Error destroying '" << pProcessor->getType();
		cerr << "' processor! No creator found for this type." << endl;
		return;
	}

	pCreator->destroyProcessor(pProcessor);
}


/**********************
* Protected functions *
**********************/

void ProcessorFactory::registerCreator(ProcessorCreator *pCreator)
{
	assert(pCreator);
	m_creators[pCreator->getType()] = pCreator;
}

void ProcessorFactory::unregisterCreator(ProcessorCreator *pCreator)
{
	assert(pCreator);
	m_creators.erase(pCreator->getType());
}
