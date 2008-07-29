#ifndef OIS2MIDI_CONVERTERMANAGER_H
#define OIS2MIDI_CONVERTERMANAGER_H

// Includes
#include "global.h"
#include "ConverterSettings
#include <OIS/OISJoyStick.h>

#ifdef OIS_LINUX_PLATFORM
typedef size_t HWND;
#endif

// Forward declarations
class RtMidiOut;
namespace OIS { class InputManager; }

namespace OIS2midi
{
	// Forward declarations

	/** Class Description */
	class ConverterManager: public OIS::JoyStickListener
	{
	public:
		// Constructors and destructor
		ConverterManager(size_t windowHandle);
		virtual ~ConverterManager();

		// Error handling
		const string &getLastError() const { return m_lastError; }

		// Other functions
		void update();
		bool sendControllerMessage(unsigned int channel, unsigned int controller, unsigned int value);
    
	protected:
		// OIS::JoyStickListener functions
		bool buttonPressed(const OIS::JoyStickEvent &arg, int button);
		bool buttonReleased(const OIS::JoyStickEvent &arg, int button);
		bool axisMoved(const OIS::JoyStickEvent &arg, int axis);
		bool sliderMoved(const OIS::JoyStickEvent &arg, int slider);
		bool povMoved(const OIS::JoyStickEvent &arg, int pov);

		// Other functions
		void initMidi();
		void destroyMidi();
		void initOIS(size_t windowHandle);
		void destroyOIS();
		void convertSignals();
		void setLastError(const string &error) const { m_lastError = error; }

		// Member variables
		RtMidiOut *m_pMidiOut;
		OIS::InputManager *m_pInputMgr;

		typedef std::vector<OIS::JoyStick *> JoyStickVector;
		JoyStickVector m_joySticks;

		// Error handling
		mutable string m_lastError;
	};
}

#endif // OIS2MIDI_CONVERTERMANAGER_H
