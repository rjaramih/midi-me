// Includes
#include "DeviceManager.h"
#include "InputDevice.h"
#include "MidiOutput.h"
using namespace MidiMe;


/*!
	Get the instance of this singleton class.
	You need to use this function to access the class,
	as the constructor is private.
*/
DeviceManager &DeviceManager::getInstance()
{
	static DeviceManager instance;
	return instance;
}


/******************************
* Constructors and destructor *
******************************/

DeviceManager::DeviceManager()
: m_windowHandle(0), m_pMidiOutput(0)
{
	m_pMidiOutput = new MidiOutput();
}

DeviceManager::~DeviceManager()
{
	if(!m_inputDevices.empty())
		cerr << "[DeviceManager] Warning: There are still input devices registered while shutting down the device manager!" << endl;

	delete m_pMidiOutput;
}


/******************
* Other functions *
******************/

const InputDeviceMap &DeviceManager::getInputDevices() const
{
	return m_inputDevices;
}

bool DeviceManager::inputDeviceExists(const string &name) const
{
	return m_inputDevices.find(name) != m_inputDevices.end();
}

unsigned int DeviceManager::numInputDevices() const
{
	return m_inputDevices.size();
}

InputDevice *DeviceManager::getInputDevice(const string &name) const
{
	InputDeviceMap::const_iterator it = m_inputDevices.find(name);
	return (it == m_inputDevices.end()) ? 0 : it->second;
}

bool DeviceManager::capture()
{
	bool success = true;

	InputDeviceMap::iterator it;
	for(it = m_inputDevices.begin(); it != m_inputDevices.end(); ++it)
		success &= it->second->capture();

	return success;
}


/**********************
* Protected functions *
**********************/

void DeviceManager::registerDevice(InputDevice *pDevice)
{
	assert(pDevice && m_inputDevices.find(pDevice->getName()) == m_inputDevices.end());
	
	m_inputDevices[pDevice->getName()] = pDevice;
	fireDeviceAdded(pDevice);
}

void DeviceManager::unregisterDevice(InputDevice *pDevice)
{
	assert(pDevice && m_inputDevices.find(pDevice->getName()) != m_inputDevices.end());
	
	fireDeviceRemoving(pDevice);
	m_inputDevices.erase(pDevice->getName());
}


/************
* Listeners *
************/

void DeviceManager::addListener(Listener *pListener)
{
	m_listeners.insert(pListener);
}

void DeviceManager::removeListener(Listener *pListener)
{
	m_listeners.erase(pListener);
}

void DeviceManager::fireDeviceAdded(InputDevice *pDevice)
{
	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onDeviceAdded(pDevice);
}

void DeviceManager::fireDeviceRemoving(InputDevice *pDevice)
{
	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onDeviceRemoving(pDevice);
}
