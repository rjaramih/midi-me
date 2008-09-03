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
#if 0
			virtual void onValue(Output *pOutput, int value) = 0;
#else
			virtual void onValue(Output *pOutput, real value) = 0;
#endif
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
#if 0
		bool sendValue(unsigned int id, int value);
#else
		bool sendValue(unsigned int id, real value);
#endif
		bool sendMinValue(unsigned int id);
		bool sendMaxValue(unsigned int id);

		// Output creation (used by derived classes)
#if 0
		Output *addOutput(unsigned int id, int minValue = 0, int maxValue = 100, bool analog = true);
#else
		Output *addOutput(unsigned int id, bool analog = true);
#endif

		// Other functions
		void destroyOutputs();
#if 0
		void fireValue(Output *pOutput, int value);
#else
		void fireValue(Output *pOutput, real value);
#endif
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
