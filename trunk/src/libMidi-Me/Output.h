#ifndef MIDIME_OUTPUT_H
#define MIDIME_OUTPUT_H

// Includes
#include "global.h"
#include "Input.h"

namespace MidiMe
{
	/** An instance of the ValueOutput class sends values to a connected ValueInput class. */
	class LIBMIDIME_API ValueOutput
	{
	public:
		// Constructors and destructor
		ValueOutput(int value): m_value(value), m_pInput(0) {}
		virtual ~ValueOutput() {}

		// Value
		int getValue() const { return m_value; }
		bool sendValueStart();
		bool sendValueStop();

		// Connection
		ValueInput *getConnectedInput() const { return m_pInput; }
		bool isConnected() const { return (m_pInput != 0); }
		void connect(ValueInput *pInput) { m_pInput = pInput; if(m_pInput) m_pInput->setOutput(this); }
		void disconnect() { if(m_pInput) m_pInput->setOutput(0); m_pInput = 0; }

	protected:
		/// The connected value input
		ValueInput *m_pInput;
		int m_value;
	};

	/** An instance of the RangeOutput class sends values to a connected RangeInput class. */
	class LIBMIDIME_API RangeOutput
	{
	public:
		// Constructors and destructor
		RangeOutput(int minValue, int maxValue): m_minValue(minValue), m_maxValue(maxValue), m_pInput(0) {}
		virtual ~RangeOutput() {}

		// Range
		int getMinValue() const { return m_minValue; }
		int getMaxValue() const { return m_maxValue; }
		bool sendValueChanged(int value);

		// Connection
		RangeInput *getConnectedInput() const { return m_pInput; }
		bool isConnected() const { return (m_pInput != 0); }
		void connect(RangeInput *pInput) { m_pInput = pInput; if(m_pInput) m_pInput->setOutput(this); }
		void disconnect() { if(m_pInput) m_pInput->setOutput(0); m_pInput = 0; }

	protected:
		/// The connected range input
		RangeInput *m_pInput;
		int m_minValue, m_maxValue;
	};
}

#endif // MIDIME_OUTPUT_H
