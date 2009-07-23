// Includes
#include "InputOISPlugin.h"
#include "JoyStick.h"
#include <libMidi-Me/DeviceManager.h>
using namespace MidiMe;

#include <OIS/OISInputManager.h>
#include <OIS/OISException.h>


/******************************
* Constructors and destructor *
******************************/

InputOISPlugin::InputOISPlugin()
: plugin::Plugin("InputOIS"), m_pInputMgr(0)
{
	setDescription("This plugin uses Open Input System (OIS) to provide joystick input devices");
}

InputOISPlugin::~InputOISPlugin()
{
}


/***************************
* plugin::Plugin functions *
***************************/

bool InputOISPlugin::start(const plugin::KeyValueMap &settings)
{
	m_settings = settings;

	if(!initOIS())
	{
		cerr << "[InputOISPlugin] Error initializing OIS!" << endl;
		return false;
	}

	m_started = true;
	return true;
}

bool InputOISPlugin::stop()
{
	if(!destroyOIS())
	{
		cerr << "[InputOISPlugin] Error destroying OIS!" << endl;
		return false;
	}

	m_started = false;
	return true;
}


/******************
* Other functions *
******************/


/**********************
* Protected functions *
**********************/

bool InputOISPlugin::initOIS()
{
	// Get the window handle to use
	size_t windowHandle = DeviceManager::getInstance().getWindowHandle();

	// Create the input system
	try
	{
		char windowHandleStr[256];
		::sprintf(windowHandleStr, "%d", windowHandle);

		OIS::ParamList params;
		params.insert(std::make_pair(std::string("WINDOW"), windowHandleStr ));

#if defined OIS_WIN32_PLATFORM
		params.insert(std::make_pair(std::string("w32_joystick"), std::string("DISCL_BACKGROUND")));
		params.insert(std::make_pair(std::string("w32_joystick"), std::string("DISCL_NONEXCLUSIVE")));
#endif

		m_pInputMgr = OIS::InputManager::createInputSystem(params);
	}
	catch(OIS::Exception &e)
	{
		cerr << "[InputOISPlugin] Error creating input system: " << string(e.eText) << endl;
		return false;
	}

	// Create all available joysticks
	//! @todo Only create joysticks that are used
	try
	{
		//int num = m_pInputMgr->numJoySticks();
		int num = m_pInputMgr->getNumberOfDevices(OIS::OISJoyStick);

		for(int i = 0; i < num; ++i)
		{
			OIS::JoyStick *pOISJoyStick = (OIS::JoyStick *) m_pInputMgr->createInputObject(OIS::OISJoyStick, true);
			JoyStick *pJoyStick = new JoyStick(pOISJoyStick);
			m_joySticks.push_back(pJoyStick);

			//cerr << "[InputOISPlugin] JoyStick found: " << pOISJoyStick->vendor() << endl;
		}
	}
	catch(OIS::Exception &e)
	{
		cerr << "[InputOISPlugin] Error initializing joystick: " << e.eText << endl;
		return false;
	}

	return true;
}

bool InputOISPlugin::destroyOIS()
{
	// Destroy joysticks
	for(unsigned int i = 0; i < m_joySticks.size(); ++i)
	{
		JoyStick *pJoyStick = m_joySticks.at(i);
		OIS::JoyStick *pOISJoyStick = pJoyStick->getOISJoyStick();

		delete pJoyStick;
		m_pInputMgr->destroyInputObject(pOISJoyStick);
	}
	m_joySticks.clear();

	// Destroy the input system
	OIS::InputManager::destroyInputSystem(m_pInputMgr);
	m_pInputMgr = 0;

	return true;
}
