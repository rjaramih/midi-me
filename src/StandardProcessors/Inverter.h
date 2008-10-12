#ifndef MIDIME_INVERTER_H
#define MIDIME_INVERTER_H

// Includes
#include "global.h"
#include <libMidi-Me/Processor.h>

namespace MidiMe
{
	// Forward declarations

	/** An inverter converts a signal value to (1 - value). */
	class Inverter: public Processor
	{
	public:
		static string type;

		// Constructors and destructor
		Inverter();
		virtual ~Inverter();

		// Other functions
    
	protected:
		// Input::Listener functions
		void onValue(Input *pInput, real value);
	};

	/** This class knows how to create/destroy duplicator processors. */
	class InverterCreator: public ProcessorCreator
	{
	public:
		// Constructors and destructor
		InverterCreator() : ProcessorCreator(Inverter::type) {}
		virtual ~InverterCreator() {}

		// ProcessorCreator functions
		Processor *createProcessor();
		void destroyProcessor(Processor *pProcessor);
	};
}

#endif // MIDIME_INVERTER_H
