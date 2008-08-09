#ifndef MIDIME_INPUT_H
#define MIDIME_INPUT_H

// Includes
#include "global.h"

namespace MidiMe
{
	// Forward declarations
	class ValueOutput;
	class RangeOutput;

	enum InputType { IT_Value, IT_Range };

	/** The base class for inputs */
	class LIBMIDIME_API Input
	{
	public:
		InputType getType() const { return m_type; }

	protected:
		Input(InputType type): m_type(type) {}
		virtual ~Input() {}
		
		InputType m_type;
	};

	/** An instance of the ValueInput class accepts values from a connected ValueOutput class. */
	class LIBMIDIME_API ValueInput: public Input
	{
	public:
		// Listener
		class Listener
		{
		public:
			virtual ~Listener() {}
			virtual void onValueStart(ValueInput *pInput) = 0;
			virtual void onValueStop(ValueInput *pInput) = 0;
		};

		// Constructors and destructor
		ValueInput(): Input(IT_Value), m_pOutput(0) {}
		virtual ~ValueInput() {}

		// Connection (handled by ValueOutput)
		ValueOutput *getConnectedOutput() const { return m_pOutput; }
		bool isConnected() const { return (m_pOutput != 0); }

	protected:
		/// The connected value output
		ValueOutput *m_pOutput;

		friend class ValueOutput;
		void setOutput(ValueOutput *pOutput) { m_pOutput = pOutput; }
		bool processValueStart(int value);
		bool processValueStop(int value);
	};

	/** An instance of the RangeInput class accepts values from a connected RangeOutput class. */
	class LIBMIDIME_API RangeInput: public Input
	{
	public:
		// Listener
		class Listener
		{
		public:
			virtual ~Listener() {}
			virtual void onValueChanged(RangeInput *pInput, int value) = 0;
		};

		// Constructors and destructor
		RangeInput(): Input(IT_Range), m_pOutput(0) {}
		virtual ~RangeInput() {}

		// Connection (handled by RangeOutput)
		RangeOutput *getConnectedOutput() const { return m_pOutput; }
		bool isConnected() const { return (m_pOutput != 0); }

	protected:
		/// The connected value output
		RangeOutput *m_pOutput;

		friend class RangeOutput;
		void setOutput(RangeOutput *pOutput) { m_pOutput = pOutput; }
		bool processValueChanged(int value);
	};
}

#endif // MIDIME_INPUT_H
