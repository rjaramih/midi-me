#ifndef MIDIME_PROCESSOR_H
#define MIDIME_PROCESSOR_H

// Includes
#include "global.h"
#include "Input.h"
#include "Output.h"
#include <set>

namespace MidiMe
{
	// Forward declarations
	class ValueInput;
	typedef std::set<ValueInput *> ValueInputSet;

	class RangeInput;
	typedef std::set<RangeInput *> RangeInputSet;

	class ValueOutput;
	typedef std::set<ValueOutput *> ValueOutputSet;

	class RangeOutput;
	typedef std::set<RangeOutput *> RangeOutputSet;

	/** This is the base class for Midi-Me processors.
		A processor has a set of value/range inputs and outputs.
		It processes the incoming signals and sends them to the outputs.
		@note You have to create a ProcessorCreator derivative that comes with this class,
		so the ProcessorFactory knows how to create and destroy processor instances.
	*/
	class LIBMIDIME_API Processor
	{
	public:
		// Constructors and destructor
		Processor(const string &type);
		virtual ~Processor();

		// Information
		const string &getType() const { return m_type; }

		// Inputs
		const ValueInputSet &getValueInputs() const;
		size_t numValueInputs() const;

		const RangeInputSet &getRangeInputs() const;
		size_t numRangeInputs() const;

		// Outputs
		const ValueOutputSet &getValueOutputs() const;
		size_t numValueOutputs();

		const RangeOutputSet &getRangeOutputs() const;
		size_t numRangeOutputs();
    
	protected:
		// Protected functions
		void clear();

		// Used by derived classes
		ValueInput *addValueInput();
		RangeInput *addRangeInput();
		ValueOutput *addValueOutput(int value);
		RangeOutput *addRangeOutput(int minValue, int maxValue);

		// Member variables
		string m_type;
		ValueInputSet m_valueInputs;
		RangeInputSet m_rangeInputs;
		ValueOutputSet m_valueOutputs;
		RangeOutputSet m_rangeOutputs;
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
