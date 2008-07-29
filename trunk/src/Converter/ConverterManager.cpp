// Includes
#include "ConverterManager.h"
#include "ButtonConverter.h"
#include "AxisConverter.h"
using namespace MidiMe;

#include <RtMidi/RtMidi.h>

#include <OIS/OISInputManager.h>
#include <OIS/OISException.h>


/******************************
* Constructors and destructor *
******************************/

ConverterManager::ConverterManager()
: m_started(false), m_pMidiOut(0), m_pInputMgr(0)
{
}

ConverterManager::~ConverterManager()
{
	if(m_started)
		stop();
}


/******************
* Other functions *
******************/

bool ConverterManager::start(size_t windowHandle, unsigned int midiPort)
{
	if(m_started)
	{
		setLastError("Already started");
		return false;
	}

	if(!initOIS(windowHandle))
		return false;

	if(!initMidi(midiPort))
		return false;

	m_started = true;
	return true;
}

bool ConverterManager::stop()
{
	if(!m_started)
	{
		setLastError("Not started");
		return false;
	}

	clearAxisConverters();

	if(!destroyMidi())
		return false;

	if(!destroyOIS())
		return false;

	m_started = false;
	return true;
}

bool ConverterManager::update()
{
	if(!m_started)
	{
		setLastError("Not started");
		return false;
	}

	// Capture joysticks
	for(unsigned int i = 0; i < m_joySticks.size(); ++i)
		m_joySticks[i]->capture();

	return true;
}

AxisConverter *ConverterManager::addAxisConverter(int axis)
{
	if(m_axisConverters.find(axis) != m_axisConverters.end())
	{
		setLastError("A converter for this axis already exists");
		return 0;
	}

	AxisConverter *pConverter = new AxisConverter(this, axis);
	m_axisConverters[axis] = pConverter;

	return pConverter;
}

bool ConverterManager::removeAxisConverter(AxisConverter *pConverter)
{
	if(!pConverter)
	{
		setLastError("NULL converter");
		return false;
	}

	return removeAxisConverter(pConverter->getAxis());
}

bool ConverterManager::removeAxisConverter(int axis)
{
	AxisConverterMap::iterator it = m_axisConverters.find(axis);
	if(it == m_axisConverters.end())
	{
		setLastError("No converter exists for this axis");
		return false;
	}

	delete it->second;
	m_axisConverters.erase(it);

	return true;
}

void ConverterManager::clearAxisConverters()
{
	AxisConverterMap::iterator it;
	for(it = m_axisConverters.begin(); it != m_axisConverters.end(); ++it)
		delete it->second;
	
	m_axisConverters.clear();
}

bool ConverterManager::sendControllerMessage(unsigned int channel, unsigned int controller, unsigned int value)
{
	if(!m_started)
	{
		setLastError("Not started");
		return false;
	}

	std::vector<unsigned char> message;
	message.push_back(176 + channel); // Controller + channel
	message.push_back(controller); // Controller ID
	message.push_back(value); // Value

	try
	{
		cerr << "[ConverterManager::DEBUG] Sending controller " << controller << " value " << value << endl;
		m_pMidiOut->sendMessage(&message);
	}
	catch(RtError &error)
	{
		setLastError("Midi error: " + error.getMessage());
		return false;
	}

	return true;
}


/**********************
* Protected functions *
**********************/

bool ConverterManager::initMidi(unsigned int midiPort)
{
	try
	{
		m_pMidiOut = new RtMidiOut();
		m_pMidiOut->openPort(midiPort);
	}
	catch(RtError &error)
	{
		setLastError("RtMidiOut error: " + error.getMessage());
		return false;
	}

	return true;
}

bool ConverterManager::destroyMidi()
{
	try
	{
		m_pMidiOut->closePort();

		delete m_pMidiOut;
		m_pMidiOut = 0;
	}
	catch(RtError &error)
	{
		setLastError("RtMidiOut error: " + error.getMessage());
		return false;
	}
	
	return true;
}

bool ConverterManager::initOIS(size_t windowHandle)
{
	int numDevices;

	// Create the input system
	try
	{
		char windowStr[256];
		::sprintf(windowStr, "%d", windowHandle);

		OIS::ParamList params;
		params.insert(std::make_pair(std::string("WINDOW"), windowStr ));

#if defined OIS_WIN32_PLATFORM
		params.insert(std::make_pair(std::string("w32_joystick"), std::string("DISCL_BACKGROUND")));
		params.insert(std::make_pair(std::string("w32_joystick"), std::string("DISCL_NONEXCLUSIVE")));
#endif

		m_pInputMgr = OIS::InputManager::createInputSystem(params);
	}
	catch(OIS::Exception &e)
	{
		setLastError("Error creating input system: " + string(e.eText));
		return false;
	}

	// JoySticks
	//! @todo Only create joysticks that are used
	try
	{
		numDevices = m_pInputMgr->numJoySticks();

		for(int i = 0; i < numDevices; ++i)
		{
			OIS::JoyStick *pJoyStick = (OIS::JoyStick *) m_pInputMgr->createInputObject(OIS::OISJoyStick, true);
			pJoyStick->setEventCallback(this);
			m_joySticks.push_back(pJoyStick);
		}
	}
	catch(OIS::Exception &e)
	{
		setLastError("Error initializing joystick: " + string(e.eText));
		return false;
	}

	return true;
}

bool ConverterManager::destroyOIS()
{
	// Destroy joysticks
	for(unsigned int i = 0; i < m_joySticks.size(); ++i)
		m_pInputMgr->destroyInputObject(m_joySticks[i]);
	m_joySticks.clear();

	// Destroy the input system
	OIS::InputManager::destroyInputSystem(m_pInputMgr);
	m_pInputMgr = 0;

	return true;
}

void ConverterManager::convertAxis(int axis, int value)
{
	if(m_axisConverters.find(axis) == m_axisConverters.end())
		return;

	m_axisConverters[axis]->processValue(value);
}

bool ConverterManager::buttonPressed(const OIS::JoyStickEvent &arg, int button)
{
	return true;
}

bool ConverterManager::buttonReleased(const OIS::JoyStickEvent &arg, int button)
{
	return true;
}

bool ConverterManager::axisMoved(const OIS::JoyStickEvent &arg, int axis)
{
	convertAxis(axis, arg.state.mAxes[axis].abs);
	return true;
}

bool ConverterManager::sliderMoved(const OIS::JoyStickEvent &arg, int slider)
{
	return true;
}

bool ConverterManager::povMoved(const OIS::JoyStickEvent &arg, int pov)
{
	return true;
}
