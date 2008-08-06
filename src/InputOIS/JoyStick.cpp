// Includes
#include "JoyStick.h"
#include <libMidi-Me/Output.h>
using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

JoyStick::JoyStick(OIS::JoyStick *pOISJoyStick)
: InputDevice(generateName(pOISJoyStick)), m_pOISJoyStick(pOISJoyStick)
{
	assert(m_pOISJoyStick);
	m_pOISJoyStick->setEventCallback(this);

	createOutputs();
}

JoyStick::~JoyStick()
{
	m_pOISJoyStick->setEventCallback(0);
}


/******************
* Other functions *
******************/


/**********************
* Protected functions *
**********************/

bool JoyStick::capture()
{
	m_pOISJoyStick->capture();
	return true;
}

bool JoyStick::buttonPressed(const OIS::JoyStickEvent &arg, int button)
{
	return sendValueStart(button);
}

bool JoyStick::buttonReleased(const OIS::JoyStickEvent &arg, int button)
{
	return sendValueStop(button);
}

bool JoyStick::axisMoved(const OIS::JoyStickEvent &arg, int axis)
{
	return sendValueChanged(axis, arg.state.mAxes[axis].abs);
}

bool JoyStick::sliderMoved(const OIS::JoyStickEvent &arg, int slider)
{
	//! @todo Implement something for this
	return true;
}

bool JoyStick::povMoved(const OIS::JoyStickEvent &arg, int pov)
{
	//! @todo Implement something for this
	return true;
}

void JoyStick::createOutputs()
{
	// Buttons
	short numButtons = m_pOISJoyStick->buttons();
	for(short i = 0; i < numButtons; ++i)
		addValueOutput(i);

	// Axes
	short numAxes = m_pOISJoyStick->axes();
	for(short i = 0; i < numAxes; ++i)
		addRangeOutput(OIS::JoyStick::MIN_AXIS, OIS::JoyStick::MAX_AXIS);

	//! @todo Pods and sliders
}

string JoyStick::generateName(OIS::JoyStick *pOISJoyStick)
{
	char strId[256];
	::sprintf(strId, "%d", pOISJoyStick->getID() + 1);

	return string("JoyStick ") + strId + " (" + pOISJoyStick->vendor() + ")";
}
