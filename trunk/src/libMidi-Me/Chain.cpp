// Includes
#include "Chain.h"
#include "ChainStart.h"
#include "ChainEnd.h"
#include "Processor.h"
#include "ProcessorFactory.h"
#include "Serializer.h"
#include "InputDevice.h"
#include "DeviceManager.h"
using namespace MidiMe;

#if 0
#include "Connection.h"
#endif

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
	clear();
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

ChainStart *Chain::addChainStart(InputDevice *pDevice, unsigned int outputID)
{
	ChainStart *pStart = new ChainStart(pDevice, outputID);
	m_startItems.insert(pStart);

	// Index the output
	m_outputs[pStart->getOutput()->getID()] = pStart->getOutput();
	
	fireStartAdded(pStart);

	m_dirty = true;
	return pStart;
}

void Chain::removeChainStart(ChainStart *pStart)
{
	fireStartRemoving(pStart);

	// Remove the output
	m_outputs.erase(pStart->getOutput()->getID());

	m_startItems.erase(pStart);
	delete pStart;

	m_dirty = true;
}

void Chain::clearChainStart()
{
	ChainStartSet::iterator it;
	for(it = m_startItems.begin(); it != m_startItems.end(); ++it)
	{
		ChainStart *pStart = *it;

		fireStartRemoving(pStart);
		m_outputs.erase(pStart->getOutput()->getID());
		delete pStart;
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
	MidiOutput *pMidi = DeviceManager::getInstance().getMidiOutput();
	ChainEnd *pEnd = new ChainEnd(pMidi);
	m_endItems.insert(pEnd);

	// Add the input
	m_inputs[pEnd->getInput()->getID()] = pEnd->getInput();

	fireEndAdded(pEnd);

	m_dirty = true;
	return pEnd;
}

void Chain::removeChainEnd(ChainEnd *pEnd)
{
	fireEndRemoving(pEnd);

	// Remove the input
	m_inputs.erase(pEnd->getInput()->getID());

	m_endItems.erase(pEnd);
	delete pEnd;

	m_dirty = true;
}

void Chain::clearChainEnd()
{
	ChainEndSet::iterator it;
	for(it = m_endItems.begin(); it != m_endItems.end(); ++it)
	{
		ChainEnd *pEnd = *it;

		fireEndRemoving(pEnd);
		m_inputs.erase(pEnd->getInput()->getID());
		delete pEnd;
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

	// Add the inputs
	const InputSet &inputs = pProcessor->getInputs();
	for(InputSet::const_iterator it = inputs.begin(); it != inputs.end(); ++it)
	{
		Input *pInput = *it;
		m_inputs[pInput->getID()] = pInput;
	}

	// Add the outputs
	const OutputSet &outputs = pProcessor->getOutputs();
	for(OutputSet::const_iterator it = outputs.begin(); it != outputs.end(); ++it)
	{
		Output *pOutput = *it;
		m_outputs[pOutput->getID()] = pOutput;
	}

	fireProcessorAdded(pProcessor);

	m_dirty = true;
	return pProcessor;
}

void Chain::removeProcessor(Processor *pProcessor)
{
	fireProcessorRemoving(pProcessor);

	// Remove the inputs
	const InputSet &inputs = pProcessor->getInputs();
	for(InputSet::const_iterator it = inputs.begin(); it != inputs.end(); ++it)
	{
		Input *pInput = *it;
		m_inputs.erase(pInput->getID());
	}

	// Remove the outputs
	const OutputSet &outputs = pProcessor->getOutputs();
	for(OutputSet::const_iterator it = outputs.begin(); it != outputs.end(); ++it)
	{
		Output *pOutput = *it;
		m_outputs.erase(pOutput->getID());
	}

	m_processors.erase(pProcessor);
	ProcessorFactory::getInstance().destroyProcessor(pProcessor);

	m_dirty = true;
}

void Chain::clearProcessors()
{
	ProcessorSet::iterator it;
	for(it = m_processors.begin(); it != m_processors.end(); ++it)
	{
		Processor *pProcessor = *it;

		fireProcessorRemoving(pProcessor);

		// Remove the inputs
		const InputSet &inputs = pProcessor->getInputs();
		for(InputSet::const_iterator it2 = inputs.begin(); it2 != inputs.end(); ++it2)
		{
			Input *pInput = *it2;
			m_inputs.erase(pInput->getID());
		}

		// Remove the outputs
		const OutputSet &outputs = pProcessor->getOutputs();
		for(OutputSet::const_iterator it2 = outputs.begin(); it2 != outputs.end(); ++it2)
		{
			Output *pOutput = *it2;
			m_outputs.erase(pOutput->getID());
		}

		ProcessorFactory::getInstance().destroyProcessor(pProcessor);
	}

	m_processors.clear();
	m_dirty = true;
}


#if 0
/**************
* Connections *
**************/

const ConnectionMap &Chain::getConnections() const
{
	return m_connections;
}

size_t Chain::numConnections() const
{
	return m_connections.size();
}

Connection *Chain::addConnection(Input *pInput, Output *pOutput)
{
	Connection *pConnection = new Connection(pInput, pOutput);
	m_connections[pOutput] = pConnection;

	fireConnectionAdded(pConnection);

	m_dirty = true;
	return pConnection;
}

void Chain::removeConnection(Connection *pConnection)
{
	fireConnectionRemoving(pConnection);

	m_connections.erase(pConnection->getOutput());
	delete pConnection;

	m_dirty = true;
}

void Chain::clearConnections()
{
	ConnectionMap::iterator it;
	for(it = m_connections.begin(); it != m_connections.end(); ++it)
	{
		Connection *pConnection = it->second;

		fireConnectionRemoving(pConnection);
		delete pConnection;
	}

	m_connections.clear();
	m_dirty = true;
}
#endif


/*********************
* Inputs and outputs *
*********************/

const InputMap &Chain::getAllInputs() const
{
	return m_inputs;
}

Input *Chain::getInput(unsigned int id) const
{
	InputMap::const_iterator it = m_inputs.find(id);
	return (it == m_inputs.end()) ? 0 : it->second;
}

const OutputMap &Chain::getAllOutputs() const
{
	return m_outputs;
}

Output *Chain::getOutput(unsigned int id) const
{
	OutputMap::const_iterator it = m_outputs.find(id);
	return (it == m_outputs.end()) ? 0 : it->second;
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

#if 0
void Chain::fireConnectionAdded(Connection *pConnection)
{
	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onConnectionAdded(pConnection);
}

void Chain::fireConnectionRemoving(Connection *pConnection)
{
	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onConnectionRemoving(pConnection);
}
#endif


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


/******************
* Other functions *
******************/

/** Step this chain (capture input devices and step processors). */
void Chain::step(float seconds)
{
	// Capture input devices
	for(ChainStartSet::iterator it = m_startItems.begin(); it != m_startItems.end(); ++it)
		(*it)->getDevice()->capture();

	// Step all processors
	for(ProcessorSet::iterator it = m_processors.begin(); it != m_processors.end(); ++it)
		(*it)->step(seconds);
}

/** Clear the whole chain
	@note The current file name will also be cleared
*/
void Chain::clear()
{
#if 0
	clearConnections();
#endif
	clearChainStart();
	clearChainEnd();
	clearProcessors();

	m_currentFile.clear();
	m_dirty = false;
}


/**********************
* Protected functions *
**********************/
