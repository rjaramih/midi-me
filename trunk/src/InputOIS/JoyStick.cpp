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
	return sendMaxValue(button);
}

bool JoyStick::buttonReleased(const OIS::JoyStickEvent &arg, int button)
{
	return sendMinValue(button);
}

bool JoyStick::axisMoved(const OIS::JoyStickEvent &arg, int axis)
{
	unsigned int id = m_pOISJoyStick->buttons() + axis;
#if 0
	return sendValue(id, arg.state.mAxes[axis].abs);
#else
	int value = arg.state.mAxes[axis].abs;
	real mappedValue = (value - OIS::JoyStick::MIN_AXIS) / (real) (OIS::JoyStick::MAX_AXIS - OIS::JoyStick::MIN_AXIS);
	return sendValue(id, mappedValue);
#endif
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
#if 0
		addOutput(i, OIS::JoyStick::MIN_AXIS, OIS::JoyStick::MAX_AXIS, false);
#else
		addOutput(i, false);
#endif

	// Axes
	short numAxes = m_pOISJoyStick->axes();
	for(short i = 0; i < numAxes; ++i)
#if 0
		addOutput(numButtons + i, OIS::JoyStick::MIN_AXIS, OIS::JoyStick::MAX_AXIS, true);
#else
		addOutput(numButtons + i, true);
#endif

	//! @todo Pods and sliders
}

string JoyStick::generateName(OIS::JoyStick *pOISJoyStick)
{
	char strId[256];
	::sprintf(strId, "%d", pOISJoyStick->getID() + 1);

	return string("JoyStick ") + strId + " (" + pOISJoyStick->vendor() + ")";
}
