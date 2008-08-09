#ifndef MIDIME_CHAINSTART_H
#define MIDIME_CHAINSTART_H

// Includes
#include "global.h"
#include <set>

namespace MidiMe
{
	// Forward declarations
	class InputDevice;
	class Output;

	/** Class Description */
	class LIBMIDIME_API ChainStart
	{
	public:
		class Listener
		{
		public:
			virtual ~Listener() {}
			virtual void onDeviceChanged(InputDevice *pDevice, InputDevice *pOldDevice) = 0;
			virtual void onOutputChanged(Output *pOutput, Output *pOldOutput) = 0;
		};

		// Constructors and destructor
		ChainStart();
		virtual ~ChainStart();

		// Device
		InputDevice *getDevice() const { return m_pDevice; }
		void setDevice(InputDevice *pDevice);

		// Output
		Output *getOutput() const { return m_pOutput; }
		void setOutput(Output *pOutput);

		// Listeners
		void addListener(Listener *pListener);
		void removeListener(Listener *pListener);
    
	protected:
		// Protected functions
		void fireDeviceChanged(InputDevice *pOldDevice);
		void fireOutputChanged(Output *pOldOutput);

		// Member variables
		InputDevice *m_pDevice;
		Output *m_pOutput;

		typedef std::set<Listener *> ListenerSet;
		ListenerSet m_listeners;
	};
}

#endif // MIDIME_CHAINSTART_H
