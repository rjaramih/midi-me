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

unsigned int InputDevice::numValueOutputs() const
{
	return m_valueOutputs.size();
}

ValueOutput *InputDevice::getValueOutput(unsigned int i) const
{
	return m_valueOutputs.at(i);
}

unsigned int InputDevice::numRangeOutputs() const
{
	return m_rangeOutputs.size();
}

RangeOutput *InputDevice::getRangeOutput(unsigned int i) const
{
	return m_rangeOutputs.at(i);
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

bool InputDevice::sendValueStart(int value)
{
	if(m_valueOutputs.size() <= (size_t) value) return false;

	ValueOutput *pOutput = m_valueOutputs.at(value);
	if(!pOutput->sendValueStart())
		return false;

	fireValueStart(pOutput);
	return true;
}

bool InputDevice::sendValueStop(int value)
{
	if(m_valueOutputs.size() <= (size_t) value) return false;

	ValueOutput *pOutput = m_valueOutputs.at(value);
	if(!pOutput->sendValueStop())
		return false;

	fireValueStop(pOutput);
	return true;
}

bool InputDevice::sendValueChanged(int id, int value)
{
	if(m_rangeOutputs.size() <= (size_t) id) return false;

	RangeOutput *pOutput = m_rangeOutputs.at(id);
	if(!pOutput->sendValueChanged(value))
		return false;

	fireValueChanged(pOutput, value);
	return true;
}

ValueOutput *InputDevice::addValueOutput(int value)
{
	ValueOutput *pOutput = new ValueOutput(value);
	m_valueOutputs.push_back(pOutput);
	return pOutput;
}

RangeOutput *InputDevice::addRangeOutput(int minValue, int maxValue)
{
	RangeOutput *pOutput = new RangeOutput(minValue, maxValue);
	m_rangeOutputs.push_back(pOutput);
	return pOutput;
}

void InputDevice::destroyOutputs()
{
	// Range outputs
	for(unsigned int i = 0; i < m_rangeOutputs.size(); ++i)
		delete m_rangeOutputs.at(i);
	m_rangeOutputs.clear();

	// Value outputs
	for(unsigned int i = 0; i < m_valueOutputs.size(); ++i)
		delete m_valueOutputs.at(i);
	m_valueOutputs.clear();
}

void InputDevice::fireValueStart(ValueOutput *pOutput)
{
	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onValueStart(pOutput);
}

void InputDevice::fireValueStop(ValueOutput *pOutput)
{
	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onValueStop(pOutput);
}

void InputDevice::fireValueChanged(RangeOutput *pOutput, int value)
{
	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onValueChanged(pOutput, value);
}
