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
		// Constructors and destructor
		ChainEnd(MidiOutput *pMidi, Input *pInput);
		virtual ~ChainEnd();

		// Information
		MidiOutput *getMidi() const { return m_pMidi; }
		Input *getInput() const { return m_pInput; }
    
	protected:
		// Member variables
		MidiOutput *m_pMidi;
		Input *m_pInput;
	};
}

#endif // MIDIME_CHAINEND_H
