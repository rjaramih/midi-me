#ifndef MIDIME_CONVERTERMANAGER_H
#define MIDIME_CONVERTERMANAGER_H

// Includes
#include "global.h"
#include <OIS/OISJoyStick.h>

// Forward declarations
class RtMidiOut;
namespace OIS { class InputManager; }

namespace MidiMe
{
	// Forward declarations
	class Converter;
	class ButtonConverter;
	class AxisConverter;

	/** Class Description */
	class ConverterManager: private OIS::JoyStickListener
	{
	public:
		// Constructors and destructor
		ConverterManager();
		virtual ~ConverterManager();

		// Error handling
		const string &getLastError() const { return m_lastError; }

		// Other functions
		bool start(size_t windowHandle, unsigned int midiPort);
		bool stop();
		bool update();

		AxisConverter *addAxisConverter(int axis);
		bool removeAxisConverter(AxisConverter *pConverter);
		bool removeAxisConverter(int axis);
		void clearAxisConverters();

		bool sendControllerMessage(unsigned int channel, unsigned int controller, unsigned int value);
    
	protected:
		// OIS::JoyStickListener functions
		bool buttonPressed(const OIS::JoyStickEvent &arg, int button);
		bool buttonReleased(const OIS::JoyStickEvent &arg, int button);
		bool axisMoved(const OIS::JoyStickEvent &arg, int axis);
		bool sliderMoved(const OIS::JoyStickEvent &arg, int slider);
		bool povMoved(const OIS::JoyStickEvent &arg, int pov);

		// Other functions
		bool initMidi(unsigned int midiPort);
		bool destroyMidi();

		bool initOIS(size_t windowHandle);
		bool destroyOIS();

		void convertAxis(int axis, int value);

		void tempTest();
		void setLastError(const string &error) const { m_lastError = error; }

		// Member variables
		bool m_started;
		RtMidiOut *m_pMidiOut;
		OIS::InputManager *m_pInputMgr;

		typedef std::vector<OIS::JoyStick *> JoyStickVector;
		JoyStickVector m_joySticks;

		typedef std::map<int, AxisConverter *> AxisConverterMap;
		AxisConverterMap m_axisConverters;

		// Error handling
		mutable string m_lastError;
	};
}

#endif // MIDIME_CONVERTERMANAGER_H
