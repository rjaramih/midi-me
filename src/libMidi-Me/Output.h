#ifndef MIDIME_OUTPUT_H
#define MIDIME_OUTPUT_H

// Includes
#include "global.h"
#include "Input.h"
#include <set>

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
		class Listener
		{
		public:
			virtual ~Listener() {}
#if 0
			virtual void onValue(Output *pOutput, int value) = 0;
#else
			virtual void onValue(Output *pOutput, real value) = 0;
#endif
		};

		// Constructors and destructors
#if 0
		Output(int minValue = 0, int maxValue = 100, bool analog = true);
#else
		Output(bool analog = true);
#endif
		virtual ~Output();

		// Connection
		Input *getConnectedInput() const { return m_pInput; }
		bool isConnected() const { return (m_pInput != 0); }
		void connect(Input *pInput) { m_pInput = pInput; if(m_pInput) m_pInput->setOutput(this); }
		void disconnect() { if(m_pInput) m_pInput->setOutput(0); m_pInput = 0; }

		// Settings
#if 0
		int getMinValue() const { return m_minValue; }
		void setMinValue(int value) { m_minValue = value; }

		int getMaxValue() const { return m_maxValue; }
		void setMaxValue(int value) { m_maxValue = value; }
#endif

		bool isAnalog() const { return m_analog; }
		void setAnalog(bool analog) { m_analog = analog; }

		// Other functions
#if 0
		void sendValue(int value);
		void sendMinValue() { sendValue(m_minValue); }
		void sendMaxValue() { sendValue(m_maxValue); }
#else
		void sendValue(real value);
		void sendMinValue() { sendValue(0); }
		void sendMaxValue() { sendValue(1); }
#endif

		// Listeners
		void addListener(Listener *pListener);
		void removeListener(Listener *pListener);

	protected:
		/// The connected input
		Input *m_pInput;

#if 0
		/// The minimum and maximum values for this output.
		int m_minValue, m_maxValue;
#endif

		/** If this is true, a value will be send between the minimum and maximum value.
			Otherwise, there will be toggled between the minimum and maximum values.
			@note This is just a hint that this output exposes (for example for widgets,
			so they can choose to visualize the output as a slider or a button).
		*/
		bool m_analog;

		typedef std::set<Listener *>ListenerSet;
		ListenerSet m_listeners;
	};
}

#endif // MIDIME_OUTPUT_H
