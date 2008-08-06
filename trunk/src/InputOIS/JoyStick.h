#ifndef MIDIME_JOYSTICK_H
#define MIDIME_JOYSTICK_H

// Includes
#include "global.h"
#include <libMidi-Me/InputDevice.h>
#include <OIS/OISJoyStick.h>

namespace MidiMe
{
	// Forward declarations

	/** Class Description */
	class JoyStick: public InputDevice, private OIS::JoyStickListener
	{
	public:
		// Constructors and destructor
		JoyStick(OIS::JoyStick *pOISJoyStick);
		virtual ~JoyStick();

		// Information
		OIS::JoyStick *getOISJoyStick() const { return m_pOISJoyStick; }

	protected:
		// Device functions
		bool capture();

		// OIS::JoyStickListener functions
		bool buttonPressed(const OIS::JoyStickEvent &arg, int button);
		bool buttonReleased(const OIS::JoyStickEvent &arg, int button);
		bool axisMoved(const OIS::JoyStickEvent &arg, int axis);
		bool sliderMoved(const OIS::JoyStickEvent &arg, int slider);
		bool povMoved(const OIS::JoyStickEvent &arg, int pov);

		// Other functions
		void createOutputs();
		static string generateName(OIS::JoyStick *pOISJoyStick);

		// Member variables
		OIS::JoyStick *m_pOISJoyStick;
	};
}

#endif // MIDIME_JOYSTICK_H
