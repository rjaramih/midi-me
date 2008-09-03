#ifndef MIDIME_CONTROLLERSIGNAL_H
#define MIDIME_CONTROLLERSIGNAL_H

// Includes
#include "global.h"
#include "Input.h"

namespace MidiMe
{
	// Forward declarations
	class MidiOutput;

	/** Connect to this input to convert the incoming value to a midi CC.
		You can set the midi channel and controller ID to use.
		You can also set the start and end values (defaulting to resp. 0 and 128).
		The incoming value range is mapped on the start-end range, linearly interpolating inbetween.
	*/
	class LIBMIDIME_API ControllerSignal: public Input, Input::Listener
	{
	public:
		// Constructors and destructor
		ControllerSignal(MidiOutput *pMidiOutput);
		virtual ~ControllerSignal();

		// Channel
		unsigned int getChannel() const { return m_channel; }
		void setChannel(unsigned int channel) { m_channel = channel; }

		// Controller ID
		unsigned int getController() const { return m_controller; }
		void setController(unsigned int controller) { m_controller = controller; }

		// Starting value (the minimum of the incoming range value will be mapped on this)
		unsigned int startValue() const { return m_startValue; }
		void setStartValue(unsigned int value) { m_startValue = value; }

		// Ending value (the maximum of the incoming range value will be mapped on this)
		unsigned int endValue() const { return m_endValue; }
		void setEndValue(unsigned int value) { m_endValue = value; }

	protected:
		// Input::Listener functions
#if 0
		void onValue(Input *pInput, int value);
#else
		void onValue(Input *pInput, real value);
#endif

		// Member variables
		MidiOutput *m_pMidiOutput;
		unsigned int m_channel, m_controller;
		unsigned int m_startValue, m_endValue;
	};
}

#endif // MIDIME_CONTROLLERSIGNAL_H
