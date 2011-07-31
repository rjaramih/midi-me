#ifndef MIDIME_MIDIOUTPUT_H
#define MIDIME_MIDIOUTPUT_H

// Includes
#include "global.h"
#include "LastError.h"
#include <set>

// Forward declarations
class RtMidiOut;

namespace MidiMe
{
	// Forward declarations

	/** Class Description */
	class LIBMIDIME_API MidiOutput: public LastError
	{
	public:
		// Constructors and destructor
		MidiOutput();
		virtual ~MidiOutput();

		// Information
		unsigned int numPorts() const;
		string getPortName(unsigned int port) const;
		bool isOpened() const { return m_opened; }
		unsigned int getOpenedPort() const { return m_midiPort; }
		bool isVirtual() const { return m_virtual; }

		// Midi functions
		bool open(unsigned int port);
		bool openVirtual();
		bool close();

		// CCs
		bool sendControllerMessage(unsigned int channel, unsigned int controller, unsigned int value);

	protected:
		// Other functions
		bool initMidi();
		bool destroyMidi();

		// Member variables
		RtMidiOut *m_pMidiOut;
		bool m_opened, m_virtual;
		unsigned int m_midiPort;
	};
}

#endif // MIDIME_MIDIOUTPUT_H
