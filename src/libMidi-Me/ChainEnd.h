#ifndef MIDIME_CHAINEND_H
#define MIDIME_CHAINEND_H

// Includes
#include "global.h"
#include <Properties/PropertyCollection.h>
#include <set>

namespace MidiMe
{
	// Forward declarations
	class MidiOutput;
	class Input;

	/** Class Description */
	class LIBMIDIME_API ChainEnd: public PropertyCollection
	{
	public:
		// Constructors and destructor
		ChainEnd(MidiOutput *pMidi, Input *pInput);
		virtual ~ChainEnd();

		// Information
		MidiOutput *getMidi() const { return m_pMidi; }
		Input *getInput() const { return m_pInput; }
    
		// Settings
		unsigned int getMidiPort() const;
		void setMidiPort(unsigned int port);
		int getCC() const;
		void setCC(int channel);

	protected:
		// Protected functions
		void createProperties();
		void destroyProperties();

		// Member variables
		MidiOutput *m_pMidi;
		Input *m_pInput;
	};
}

#endif // MIDIME_CHAINEND_H
