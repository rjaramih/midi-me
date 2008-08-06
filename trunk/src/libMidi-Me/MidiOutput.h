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
	class ControllerSignal;
	typedef std::set<ControllerSignal *> ControllerSignalSet;

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

		// Midi functions
		bool open(unsigned int port);
		bool close();

		// CCs
		ControllerSignal *createControllerSignal();
		void destroyControllerSignal(ControllerSignal *pController);

		bool sendControllerMessage(unsigned int channel, unsigned int controller, unsigned int value);

	protected:
		// Other functions
		bool initMidi();
		bool destroyMidi();

		// Member variables
		RtMidiOut *m_pMidiOut;
		bool m_opened;
		unsigned int m_midiPort;

		ControllerSignalSet m_controllerSignals;
	};
}

#endif // MIDIME_MIDIOUTPUT_H
