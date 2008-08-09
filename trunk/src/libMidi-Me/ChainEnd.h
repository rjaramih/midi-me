#ifndef MIDIME_CHAINEND_H
#define MIDIME_CHAINEND_H

// Includes
#include "global.h"

namespace MidiMe
{
	// Forward declarations
	class MidiOutput;
	class Input;

	/** Class Description */
	class LIBMIDIME_API ChainEnd
	{
	public:
		// Constructors and destructor
		ChainEnd();
		virtual ~ChainEnd();

		// Device
		MidiOutput *getMidi() const { return m_pMidi; }
		void setMidi(MidiOutput *pMidi) { m_pMidi = pMidi; }

		// Input
		Input *getInput() const { return m_pInput; }
		void setInput(Input *pInput) { m_pInput = pInput; }
    
	protected:
		// Member variables
		MidiOutput *m_pMidi;
		Input *m_pInput;
	};
}

#endif // MIDIME_CHAINEND_H
