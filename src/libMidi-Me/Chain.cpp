// Includes
#include "Chain.h"
#include "ChainStart.h"
#include "ChainEnd.h"
#include "Processor.h"
#include "ProcessorFactory.h"
#include "Serializer.h"
using namespace MidiMe;

#include <RtMidi/RtMidi.h>


/******************************
* Constructors and destructor *
******************************/

Chain::Chain()
: m_started(false), m_dirty(false)
{
}

Chain::~Chain()
{
	clearChainStart();
	clearChainEnd();
	clearProcessors();
}


/**************
* Chain start *
**************/

const ChainStartSet &Chain::getChainStart() const
{
	return m_startItems;
}

size_t Chain::numChainStartItems() const
{
	return m_startItems.size();
}

ChainStart *Chain::addChainStart(Output *pOutput)
{
	ChainStart *pStart = new ChainStart(pOutput);
	m_startItems.insert(pStart);
	
	fireStartAdded(pStart);

	m_dirty = true;
	return pStart;
}

void Chain::removeChainStart(ChainStart *pStart)
{
	fireStartRemoving(pStart);

	m_startItems.erase(pStart);
	delete pStart;

	m_dirty = true;
}

void Chain::clearChainStart()
{
	ChainStartSet::iterator it;
	for(it = m_startItems.begin(); it != m_startItems.end(); ++it)
	{
		fireStartRemoving(*it);
		delete *it;
	}

	m_startItems.clear();
	m_dirty = true;
}


/************
* Chain end *
************/

const ChainEndSet &Chain::getChainEnd() const
{
	return m_endItems;
}

size_t Chain::numChainEndItems() const
{
	return m_endItems.size();
}

ChainEnd *Chain::addChainEnd()
{
	ChainEnd *pEnd = new ChainEnd();
	m_endItems.insert(pEnd);

	fireEndAdded(pEnd);

	m_dirty = true;
	return pEnd;
}

void Chain::removeChainEnd(ChainEnd *pEnd)
{
	fireEndRemoving(pEnd);

	m_endItems.erase(pEnd);
	delete pEnd;

	m_dirty = true;
}

void Chain::clearChainEnd()
{
	ChainEndSet::iterator it;
	for(it = m_endItems.begin(); it != m_endItems.end(); ++it)
	{
		fireEndRemoving(*it);
		delete *it;
	}

	m_endItems.clear();
	m_dirty = true;
}


/*************
* Processors *
*************/

const ProcessorSet &Chain::getProcessors() const
{
	return m_processors;
}

size_t Chain::numProcessors() const
{
	return m_processors.size();
}

Processor *Chain::addProcessor(const string &type)
{
	Processor *pProcessor = ProcessorFactory::getInstance().createProcessor(type);
	if(!pProcessor)
		return 0;

	m_processors.insert(pProcessor);
	fireProcessorAdded(pProcessor);

	m_dirty = true;
	return pProcessor;
}

void Chain::removeProcessor(Processor *pProcessor)
{
	fireProcessorRemoving(pProcessor);

	m_processors.erase(pProcessor);
	ProcessorFactory::getInstance().destroyProcessor(pProcessor);

	m_dirty = true;
}

void Chain::clearProcessors()
{
	ProcessorSet::iterator it;
	for(it = m_processors.begin(); it != m_processors.end(); ++it)
	{
		fireProcessorRemoving(*it);
		ProcessorFactory::getInstance().destroyProcessor(*it);
	}

	m_processors.clear();
	m_dirty = true;
}


/************
* Listeners *
************/

void Chain::addListener(Listener *pListener)
{
	m_listeners.insert(pListener);
}

void Chain::removeListener(Listener *pListener)
{
	m_listeners.erase(pListener);
}

void Chain::fireStartAdded(ChainStart *pStart)
{
	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onStartAdded(pStart);
}

void Chain::fireStartRemoving(ChainStart *pStart)
{
	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onStartRemoving(pStart);
}

void Chain::fireEndAdded(ChainEnd *pEnd)
{
	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onEndAdded(pEnd);
}

void Chain::fireEndRemoving(ChainEnd *pEnd)
{
	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onEndRemoving(pEnd);
}

void Chain::fireProcessorAdded(Processor *pProcessor)
{
	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onProcessorAdded(pProcessor);
}

void Chain::fireProcessorRemoving(Processor *pProcessor)
{
	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onProcessorRemoving(pProcessor);
}



/****************
* Serialization *
****************/

bool Chain::load(const string &filename)
{
	Serializer loader;
	if(!loader.load(this, filename))
	{
		setLastError("Error loading settings from '" + filename + "': " + loader.getLastError());
		return false;
	}

	m_currentFile = filename;
	m_dirty = false;

	return true;
}

/** Save this chain to the currently opened file */
bool Chain::save()
{
	if(m_currentFile.empty())
	{
		setLastError("No currently opened file");
		return false;
	}

	return save(m_currentFile);
}

bool Chain::save(const string &filename)
{
	Serializer saver;
	if(!saver.save(this, filename))
	{
		setLastError("Error saving settings to '" + filename + "': " + saver.getLastError());
		return false;
	}

	m_currentFile = filename;
	m_dirty = false;

	return true;
}


/**********************
* Protected functions *
**********************/
