#ifndef MIDIME_OUTPUT_H
#define MIDIME_OUTPUT_H

// Includes
#include "global.h"
#include "Input.h"

namespace MidiMe
{
	/** This class represents an output that you can connect to an input.
		An output has a mininum and maximum value and can be analog or digital
		(meaning the value will be between the minimum and maximum value,
		or toggled between the minimum and maximum value).
	*/
	class LIBMIDIME_API Output
	{
	public:
		// Constructors and destructors
		Output(int minValue = 0, int maxValue = 100, bool analog = true);
		virtual ~Output();

		// Connection
		Input *getConnectedInput() const { return m_pInput; }
		bool isConnected() const { return (m_pInput != 0); }
		void connect(Input *pInput) { m_pInput = pInput; if(m_pInput) m_pInput->setOutput(this); }
		void disconnect() { if(m_pInput) m_pInput->setOutput(0); m_pInput = 0; }

		// Settings
		int getMinValue() const { return m_minValue; }
		void setMinValue(int value) { m_minValue = value; }

		int getMaxValue() const { return m_maxValue; }
		void setMaxValue(int value) { m_maxValue = value; }

		bool isAnalog() const { return m_analog; }
		void setAnalog(bool analog) { m_analog = analog; }

		// Other functions
		void sendValue(int value);
		void sendMinValue() { sendValue(m_minValue); }
		void sendMaxValue() { sendValue(m_maxValue); }

	protected:
		/// The connected input
		Input *m_pInput;

		/// The minimum and maximum values for this output.
		int m_minValue, m_maxValue;

		/** If this is true, a value will be send between the minimum and maximum value.
			Otherwise, there will be toggled between the minimum and maximum values.
			@note This is just a hint that this output exposes (for example for widgets,
			so they can choose to visualize the output as a slider or a button).
		*/
		bool m_analog;
	};
}

#endif // MIDIME_OUTPUT_H
