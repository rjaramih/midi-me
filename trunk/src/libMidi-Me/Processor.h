#ifndef MIDIME_PROCESSOR_H
#define MIDIME_PROCESSOR_H

// Includes
#include "global.h"
#include "Input.h"
#include "Output.h"
#include <Properties/PropertyCollection.h>
#include <set>

namespace MidiMe
{
	// Forward declarations
	class Input;
	typedef std::set<Input *> InputSet;

	class Output;
	typedef std::set<Output *> OutputSet;

	/** This is the base class for Midi-Me processors.
		A processor has a set of inputs and outputs.
		It processes the incoming signals and sends them to the outputs.
		@note You have to create a ProcessorCreator derivative that comes with this class,
		so the ProcessorFactory knows how to create and destroy processor instances.
	*/
	class LIBMIDIME_API Processor: protected Input::Listener, public PropertyCollection
	{
	public:
		// Constructors and destructor
		Processor(const string &type);
		virtual ~Processor();

		// Information
		const string &getType() const { return m_type; }

		// Inputs
		const InputSet &getInputs() const;
		size_t numInputs() const;

		// Outputs
		const OutputSet &getOutputs() const;
		size_t numOutputs();

		// Step function
		virtual void step(float seconds) {}
    
	protected:
		// Protected functions
		void clear();

		// Used by derived classes
#if 0
		Input *addInput(int minValue = 0, int maxValue = 100, bool inverted = false);
		Output *addOutput(int minValue = 0, int maxValue = 100, bool analog = true);
#else
		Input *addInput(bool inverted = false);
		Output *addOutput(bool analog = true);
#endif

		// Member variables
		string m_type;
		InputSet m_inputs;
		OutputSet m_outputs;
	};

	/** Derive from this class to register a processor type in the ProcessorFactory.
		@note ProcessorCreators automatically register themselves in the ProcessorFactory.
	*/
	class LIBMIDIME_API ProcessorCreator
	{
	public:
		// Constructors and destructors
		ProcessorCreator(const string &type);
		virtual ~ProcessorCreator();

		// Information
		const string &getType() const { return m_type; }

		// Processor creation/destruction
		virtual Processor *createProcessor() = 0;
		virtual void destroyProcessor(Processor *pProcessor) = 0;

	protected:
		/// The type of the processor
		string m_type;
	};
}

#endif // MIDIME_PROCESSOR_H
