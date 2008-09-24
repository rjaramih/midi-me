#ifndef MIDIME_SPLITTER_H
#define MIDIME_SPLITTER_H

// Includes
#include "global.h"
#include <libMidi-Me/Processor.h>

namespace MidiMe
{
	// Forward declarations

	/** A splitter is a processor that splits its input signal into two different signals.
		You can set the value at which to split the signal. Value above this will go to one signal,
		values above will go to the second signal.
	*/
	class Splitter: public Processor
	{
	public:
		static string type;

		// Constructors and destructor
		Splitter();
		virtual ~Splitter();

		// Other functions
		real getSplitValue() const { return m_splitValue; }
		void setSplitValue(real value) { m_splitValue = value; }
    
	protected:
		// Input::Listener functions
		void onValue(Input *pInput, real value);

		// Protected functions
		void createProperties();
		void destroyProperties();

		// Member variables
		real m_splitValue;
		Input *m_pInput;
		Output *m_pOutput1, *m_pOutput2;
	};

	/** This class knows how to create/destroy splitter processors. */
	class SplitterCreator: public ProcessorCreator
	{
	public:
		// Constructors and destructor
		SplitterCreator() : ProcessorCreator(Splitter::type) {}
		virtual ~SplitterCreator() {}

		// ProcessorCreator functions
		Processor *createProcessor();
		void destroyProcessor(Processor *pProcessor);
	};
}

#endif // MIDIME_SPLITTER_H
