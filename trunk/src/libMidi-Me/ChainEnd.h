#ifndef MIDIME_CHAINEND_H
#define MIDIME_CHAINEND_H

// Includes
#include "global.h"
#include <set>

namespace MidiMe
{
	// Forward declarations
	class MidiOutput;
	class Input;

	/** Class Description */
	class LIBMIDIME_API ChainEnd
	{
	public:
		class Listener
		{
		public:
			virtual ~Listener() {}
			virtual void onMidiChanged(MidiOutput *pMidi, MidiOutput *pOldMidi) = 0;
			virtual void onInputChanged(Input *pInput, Input *pOldInput) = 0;
		};

		// Constructors and destructor
		ChainEnd();
		virtual ~ChainEnd();

		// Device
		MidiOutput *getMidi() const { return m_pMidi; }
		void setMidi(MidiOutput *pMidi);

		// Input
		Input *getInput() const { return m_pInput; }
		void setInput(Input *pInput);
    
		// Listeners
		void addListener(Listener *pListener);
		void removeListener(Listener *pListener);
    
	protected:
		// Protected functions
		void fireMidiChanged(MidiOutput *pOldMidi);
		void fireInputChanged(Input *pOldInput);

		// Member variables
		MidiOutput *m_pMidi;
		Input *m_pInput;

		typedef std::set<Listener *> ListenerSet;
		ListenerSet m_listeners;
	};
}

#endif // MIDIME_CHAINEND_H
