#ifndef MIDIME_DUPLICATOR_H
#define MIDIME_DUPLICATOR_H

// Includes
#include "global.h"
#include <libMidi-Me/Processor.h>

namespace MidiMe
{
	// Forward declarations

	/** A duplicator is a processor that duplicates its input signal into two signals.
		@todo Support a variable amount of duplicate channels
	*/
	class Duplicator: public Processor
	{
	public:
		static string type;

		// Constructors and destructor
		Duplicator();
		virtual ~Duplicator();

		// Other functions
    
	protected:
		// Input::Listener functions
		void onValue(Input *pInput, real value);
	};

	/** This class knows how to create/destroy duplicator processors. */
	class DuplicatorCreator: public ProcessorCreator
	{
	public:
		// Constructors and destructor
		DuplicatorCreator() : ProcessorCreator(Duplicator::type) {}
		virtual ~DuplicatorCreator() {}

		// ProcessorCreator functions
		Processor *createProcessor();
		void destroyProcessor(Processor *pProcessor);
	};
}

#endif // MIDIME_DUPLICATOR_H
