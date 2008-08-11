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
			virtual void onValue(Input *pInput, int value) = 0;
		};

		// Constructors and destructors
		Input(int minValue = 0, int maxValue = 100, bool inverted = false);
		virtual ~Input();

		// Incoming connection (handled by Output)
		Output *getConnectedOutput() const { return m_pOutput; }
		bool isConnected() const { return (m_pOutput != 0); }

		// Settings
		int getMinValue() const { return m_minValue; }
		void setMinValue(int value) { m_minValue = value; }

		int getMaxValue() const { return m_maxValue; }
		void setMaxValue(int value) { m_maxValue = value; }

		bool isInverted() const { return m_inverted; }
		void setInverted(bool inverted) { m_inverted = inverted; }

		// Listeners
		void addListener(Listener *pListener);
		void removeListener(Listener *pListener);

	protected:
		/// The connected output
		Output *m_pOutput;
		/// The minimum and maximum values for this input. Incoming values will be mapped between these two.
		int m_minValue, m_maxValue;
		/// If this is true, the minimum value of a connected input will be mapped on the maximum value of this input.
		bool m_inverted;

		friend class Output;
		void setOutput(Output *pOutput) { m_pOutput = pOutput; }
		void processValue(int value);

		typedef std::set<Listener *>ListenerSet;
		ListenerSet m_listeners;
	};
}

#endif // MIDIME_INPUT_H
