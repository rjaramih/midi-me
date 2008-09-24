#ifndef MIDIME_DELAY_H
#define MIDIME_DELAY_H

// Includes
#include "global.h"
#include <libMidi-Me/Processor.h>
#include <map>

namespace MidiMe
{
	// Forward declarations

	/** A delay processor delays the incoming signal.
		@warning Because the values have to be recorded for the duration of the delay,
			this class' memory use will increase with the delay value.
	*/
	class Delay: public Processor
	{
	public:
		static string type;

		// Constructors and destructor
		Delay();
		virtual ~Delay();

		// Processor functions
		void step(float seconds);

		// Other functions
		float getDelay() const { return m_delay; }
		void setDelay(float seconds) { m_delay = seconds; }
    
	protected:
		// Input::Listener functions
		void onValue(Input *pInput, real value);

		// Protected functions
		void createProperties();
		void destroyProperties();

		//! The delay, in seconds
		float m_delay;

		//! The current time (starts at 0 when the processor is created)
		float m_currentTime;

		//! The recorded values
		typedef std::map<float, real> TimeValueMap;
		TimeValueMap m_values;
	};

	/** This class knows how to create/destroy duplicator processors. */
	class DelayCreator: public ProcessorCreator
	{
	public:
		// Constructors and destructor
		DelayCreator() : ProcessorCreator(Delay::type) {}
		virtual ~DelayCreator() {}

		// ProcessorCreator functions
		Processor *createProcessor();
		void destroyProcessor(Processor *pProcessor);
	};
}

#endif // MIDIME_DELAY_H
