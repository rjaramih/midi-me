#ifndef MIDIME_INPUT_H
#define MIDIME_INPUT_H

// Includes
#include "global.h"
#include <set>

namespace MidiMe
{
	// Forward declarations
	class Output;

	/** This class represents an input to connect an output with.
		An input has a mininum and maximum value and can be inverted.
		
		The input will automatically map the incoming value from an output between the minimum and maximum
		value of this input when sending the value to the listeners.
		
		If you invert the input, the minimum value of the connected output will be mapped
		to the maximum value of the input.
	*/
	class LIBMIDIME_API Input
	{
	public:
		class Listener
		{
		public:
			virtual ~Listener() {}
			virtual void onValue(Input *pInput, real value) = 0;
		};

		// Constructors and destructors
		Input(bool inverted = false);
		virtual ~Input();

		// Information
		unsigned int getID() const { return m_id; }
		real getCurrentValue() const { return m_value; }

		// Incoming connection (handled by Output)
		Output *getConnectedOutput() const { return m_pOutput; }
		bool isConnected() const { return (m_pOutput != 0); }

		// Settings
		bool isInverted() const { return m_inverted; }
		void setInverted(bool inverted) { m_inverted = inverted; }

		// Listeners
		void addListener(Listener *pListener);
		void removeListener(Listener *pListener);

	protected:
		/// The unique ID for this input
		unsigned int m_id;

		/// The current value
		real m_value;

		/// The connected output
		Output *m_pOutput;

		/// If this is true, the value reported will be 1 - value.
		bool m_inverted;

		friend class Output;
		void setOutput(Output *pOutput) { m_pOutput = pOutput; }
		void processValue(real value);

		// Listeners
		typedef std::set<Listener *>ListenerSet;
		ListenerSet m_listeners;
	};
}

#endif // MIDIME_INPUT_H
