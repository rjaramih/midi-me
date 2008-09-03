#ifndef MIDIME_OUTPUT_H
#define MIDIME_OUTPUT_H

// Includes
#include "global.h"
#include "Input.h"
#include <set>

namespace MidiMe
{
	/** This class represents an output that you can connect to an input.
		An analog output sends values between 0 and 1.
		A digital output sends 0 or 1.
	*/
	class LIBMIDIME_API Output
	{
	public:
		class Listener
		{
		public:
			virtual ~Listener() {}
			virtual void onValue(Output *pOutput, real value) = 0;
		};

		// Constructors and destructors
		Output(bool analog = true);
		virtual ~Output();

		// Connection
		Input *getConnectedInput() const { return m_pInput; }
		bool isConnected() const { return (m_pInput != 0); }
		void connect(Input *pInput) { m_pInput = pInput; if(m_pInput) m_pInput->setOutput(this); }
		void disconnect() { if(m_pInput) m_pInput->setOutput(0); m_pInput = 0; }

		// Information
		bool isAnalog() const { return m_analog; }

		// Other functions
		void sendValue(real value);
		void sendMinValue() { sendValue(0); }
		void sendMaxValue() { sendValue(1); }

		// Listeners
		void addListener(Listener *pListener);
		void removeListener(Listener *pListener);

	protected:
		/// The connected input
		Input *m_pInput;

		/** If this is true, a value will be send between 0 and 1.
			Otherwise, there will be toggled between 0 and 1.
			@note This is just a hint that this output exposes (for example for widgets,
			so they can choose to visualize the output as a slider or a button).
		*/
		bool m_analog;

		// Listeners
		typedef std::set<Listener *>ListenerSet;
		ListenerSet m_listeners;
	};
}

#endif // MIDIME_OUTPUT_H
