#ifndef MIDIME_CHAINEND_H
#define MIDIME_CHAINEND_H

// Includes
#include "global.h"
#include "Input.h"
#include <Properties/PropertyCollection.h>
#include <set>

namespace MidiMe
{
	// Forward declarations
	class MidiOutput;
	class Input;

	/** Connect to this input to convert the incoming value to a midi CC.
		You can set the midi channel and controller ID to use.
		You can also set the start and end values (defaulting to resp. 0 and 128).
		The incoming value range is mapped on the start-end range, linearly interpolating inbetween.
	*/
	class LIBMIDIME_API ChainEnd: public PropertyCollection, protected Input::Listener
	{
	public:
		// Constructors and destructor
		ChainEnd(MidiOutput *pMidi);
		virtual ~ChainEnd();

		// Information
		Input *getInput() const { return m_pInput; }
		MidiOutput *getMidi() const { return m_pMidi; }

		// Channel
		unsigned int getChannel() const { return m_channel; }
		void setChannel(unsigned int channel) { m_channel = channel; }

		// Controller ID
		unsigned int getController() const { return m_controller; }
		void setController(unsigned int controller) { m_controller = controller; }

		// Starting value (the minimum of the incoming range value will be mapped on this)
		unsigned int getStartValue() const { return m_startValue; }
		void setStartValue(unsigned int value) { m_startValue = value; }

		// Ending value (the maximum of the incoming range value will be mapped on this)
		unsigned int getEndValue() const { return m_endValue; }
		void setEndValue(unsigned int value) { m_endValue = value; }

	protected:
		// Input::Listener functions
		void onValue(Input *pInput, real value);

		// Protected functions
		void createProperties();
		void destroyProperties();

		// Member variables
		Input *m_pInput;
		MidiOutput *m_pMidi;
		unsigned int m_channel, m_controller;
		unsigned int m_startValue, m_endValue;
	};
}

#endif // MIDIME_CHAINEND_H
