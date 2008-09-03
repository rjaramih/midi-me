// Includes
#include "InputDevice.h"
#include "DeviceManager.h"
#include "Input.h"
#include "Output.h"
using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

InputDevice::InputDevice(const string &name)
: m_name(name)
{
	// Register this class in the device manager
	DeviceManager::getInstance().registerDevice(this);
}

InputDevice::~InputDevice()
{
	// Destroy the outputs
	destroyOutputs();

	// Unregister this class in the device manager
	DeviceManager::getInstance().unregisterDevice(this);
}


/******************
* Other functions *
******************/

const OutputMap &InputDevice::getAllOutputs() const
{
	return m_outputs;
}

unsigned int InputDevice::numOutputs() const
{
	return m_outputs.size();
}

bool InputDevice::outputExists(unsigned int id) const
{
	return m_outputs.find(id) != m_outputs.end();
}

Output *InputDevice::getOutput(unsigned int id) const
{
	OutputMap::const_iterator it = m_outputs.find(id);
	return (it == m_outputs.end()) ? 0 : it->second;
}

void InputDevice::addListener(Listener *pListener)
{
	m_listeners.insert(pListener);
}

void InputDevice::removeListener(Listener *pListener)
{
	m_listeners.erase(pListener);
}


/**********************
* Protected functions *
**********************/

#if 0
bool InputDevice::sendValue(unsigned int id, int value)
#else
bool InputDevice::sendValue(unsigned int id, real value)
#endif
{
	Output *pOutput = getOutput(id);
	if(!pOutput)
		return false;

	pOutput->sendValue(value);

	fireValue(pOutput, value);
	return true;
}

bool InputDevice::sendMinValue(unsigned int id)
{
	Output *pOutput = getOutput(id);
	if(!pOutput)
		return false;

	pOutput->sendMinValue();

	fireMinValue(pOutput);
	return true;
}

bool InputDevice::sendMaxValue(unsigned int id)
{
	Output *pOutput = getOutput(id);
	if(!pOutput)
		return false;

	pOutput->sendMaxValue();

	fireMaxValue(pOutput);
	return true;
}

#if 0
Output *InputDevice::addOutput(unsigned int id, int minValue, int maxValue, bool analog)
#else
Output *InputDevice::addOutput(unsigned int id, bool analog)
#endif
{
	if(outputExists(id))
		return 0;
#if 0
	Output *pOutput = new Output(minValue, maxValue, analog);
#else
	Output *pOutput = new Output(analog);
#endif
	m_outputs[id] = pOutput;
	return pOutput;
}

void InputDevice::destroyOutputs()
{
	OutputMap::iterator it;
	for(it = m_outputs.begin(); it != m_outputs.end(); ++it)
		delete it->second;
	m_outputs.clear();
}

#if 0
void InputDevice::fireValue(Output *pOutput, int value)
#else
void InputDevice::fireValue(Output *pOutput, real value)
#endif
{
	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onValue(pOutput, value);
}

void InputDevice::fireMinValue(Output *pOutput)
{
#if 0
	int value = pOutput->getMinValue();
#else
	real value = 0;
#endif

	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onValue(pOutput, value);
}

void InputDevice::fireMaxValue(Output *pOutput)
{
#if 0
	int value = pOutput->getMaxValue();
#else
	real value = 1;
#endif

	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onValue(pOutput, value);
}
