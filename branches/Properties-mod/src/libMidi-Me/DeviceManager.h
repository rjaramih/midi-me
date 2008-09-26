#ifndef MIDIME_DEVICEMANAGER_H
#define MIDIME_DEVICEMANAGER_H

// Includes
#include "global.h"
#include "LastError.h"
#include <map>
#include <set>

namespace MidiMe
{
	// Forward declarations
	class InputDevice;
	typedef std::map<string, InputDevice *> InputDeviceMap;

	class MidiOutput;

	/** This singleton manages the available input and output devices.
		When a device is instantiated, it automatically registers itself here.

		For the moment, there is only one midi-out device as output.
		@todo Support multiple output devices
	*/
	class LIBMIDIME_API DeviceManager: public LastError
	{
	public:
		class Listener
		{
		public:
			virtual ~Listener() {}
			/// Called right after an input device has successfully registered itself
			virtual void onDeviceAdded(InputDevice *pDevice) = 0;
			/// Called right before an input device is going to uregister itself
			virtual void onDeviceRemoving(InputDevice *pDevice) = 0;
		};

	private:
		// Private constructors and destructor
		DeviceManager();
		DeviceManager(const DeviceManager &source); //!< Copy constructor, not implemented
		virtual ~DeviceManager();

		//! Private assignment operator, not implemented
		DeviceManager &operator =(const DeviceManager &source);

	public:
		// Singleton function
		static DeviceManager &getInstance();

		// Input devices
		const InputDeviceMap &getInputDevices() const;
		bool inputDeviceExists(const string &name) const;
		unsigned int numInputDevices() const;
		InputDevice *getInputDevice(const string &name) const;

		bool capture();

		// Output devices
		MidiOutput *getMidiOutput() const { return m_pMidiOutput; }

		// Listeners
		void addListener(Listener *pListener);
		void removeListener(Listener *pListener);

		// Window handle
		void setWindowHandle(size_t windowHandle) { m_windowHandle = windowHandle; }
		size_t getWindowHandle() const { return m_windowHandle; }

	private:
		// Member variables
		InputDeviceMap m_inputDevices;
		MidiOutput *m_pMidiOutput;
		size_t m_windowHandle;

		typedef std::set<Listener *> ListenerSet;
		ListenerSet m_listeners;

		// Devices register themselves
		void registerDevice(InputDevice *pDevice);
		void unregisterDevice(InputDevice *pDevice);
		friend class InputDevice;

		// Other functions
		void fireDeviceAdded(InputDevice *pDevice);
		void fireDeviceRemoving(InputDevice *pDevice);
	};
}

#endif // MIDIME_DEVICEMANAGER_H
