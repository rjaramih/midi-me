#ifndef MIDIME_INPUTDEVICE_H
#define MIDIME_INPUTDEVICE_H

// Includes
#include "global.h"
#include <map>
#include <set>

namespace MidiMe
{
	// Forward declarations
	class Output;
	typedef std::map<unsigned int, Output *> OutputMap;

	/** This is the base class for a device that provides signals to Midi-Me.
		Derive from this class to provide input from any device you like. Instances of an InputDevice
		are automatically registered in the device manager, so they become available to Midi-Me.
		The name of the device has to be unique.
	*/
	class LIBMIDIME_API InputDevice
	{
	public:
		// Derive from this class and register yourself to receive output events
		class LIBMIDIME_API Listener
		{
		public:
			virtual ~Listener() {}
			/// Called when there is a signal in on of the outputs
			virtual void onValue(Output *pOutput, real value) = 0;
		};

		// Constructors and destructor
		InputDevice(const string &name);
		virtual ~InputDevice();

		// Information
		const string &getName() const { return m_name; }

		// Outputs
		const OutputMap &getAllOutputs() const;
		unsigned int numOutputs() const;
		bool outputExists(unsigned int id) const;
		Output *getOutput(unsigned int id) const;

		// Listeners
		void addListener(Listener *pListener);
		void removeListener(Listener *pListener);

		/// Capture the input device and generate events
		virtual bool capture() = 0;

	protected:
		/// Derived classes call this to send a signal
		bool sendValue(unsigned int id, real value);
		bool sendMinValue(unsigned int id);
		bool sendMaxValue(unsigned int id);

		// Output creation (used by derived classes)
		Output *addOutput(unsigned int id, bool analog = true);

		// Other functions
		void destroyOutputs();
		void fireValue(Output *pOutput, real value);
		void fireMinValue(Output *pOutput);
		void fireMaxValue(Output *pOutput);

		// Member variables
		string m_name; //!< The unique name for this input device
		OutputMap m_outputs;

		typedef std::set<Listener *> ListenerSet;
		ListenerSet m_listeners;
	};
}

#endif // MIDIME_INPUTDEVICE_H
