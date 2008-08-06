#ifndef MIDIME_INPUTDEVICE_H
#define MIDIME_INPUTDEVICE_H

// Includes
#include "global.h"
#include <vector>
#include <set>

namespace MidiMe
{
	// Forward declarations
	class ValueOutput;
	class RangeOutput;

	/** This is the base class for a device that provides values or ranges of values to Midi-Me.
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
			/// Called when there is a start signal in a value output
			virtual void onValueStart(ValueOutput *pOutput) = 0;
			/// Called when there is a stop signal in a value output
			virtual void onValueStop(ValueOutput *pOutput) = 0;
			/// Called when there is a value change in a range output
			virtual void onValueChanged(RangeOutput *pOutput, int value) = 0;
		};

		// Constructors and destructor
		InputDevice(const string &name);
		virtual ~InputDevice();

		// Information
		const string &getName() const { return m_name; }

		// Value outputs
		unsigned int numValueOutputs() const;
		ValueOutput *getValueOutput(unsigned int i) const;

		// Range outputs
		unsigned int numRangeOutputs() const;
		RangeOutput *getRangeOutput(unsigned int i) const;

		// Listeners
		void addListener(Listener *pListener);
		void removeListener(Listener *pListener);

		/// Capture the input device and generate events
		virtual bool capture() = 0;

	protected:
		/// Derived classes call this to send a value start signal (value output)
		bool sendValueStart(int value);
		/// Derived classes call this to send a value stop signal (value output)
		bool sendValueStop(int value);
		/// Derived classes call this to send a value change signal (range output)
		bool sendValueChanged(int id, int value);

		// Output creation (used by derived classes)
		ValueOutput *addValueOutput(int value);
		RangeOutput *addRangeOutput(int minValue, int maxValue);

		// Other functions
		void destroyOutputs();
		void fireValueStart(ValueOutput *pOutput);
		void fireValueStop(ValueOutput *pOutput);
		void fireValueChanged(RangeOutput *pOutput, int value);

		// Member variables
		string m_name; //!< The unique name for this input device
		
		typedef std::vector<ValueOutput *> ValueOutputVector;
		ValueOutputVector m_valueOutputs;

		typedef std::vector<RangeOutput *> RangeOutputVector;
		RangeOutputVector m_rangeOutputs;

		typedef std::set<Listener *> ListenerSet;
		ListenerSet m_listeners;
	};
}

#endif // MIDIME_INPUTDEVICE_H
