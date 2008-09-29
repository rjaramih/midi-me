#ifndef MIDIME_OUTPUT_H
#define MIDIME_OUTPUT_H

// Includes
#include "global.h"
#include <set>

namespace MidiMe
{
	// Forward declarations
	class Connection;

	/** This class represents an output, that can be connected to an input.
		An analog output sends values between 0 and 1.
		A digital output sends 0 or 1.
	*/
	class LIBMIDIME_API Output
	{
	public:
		class Listener
		{
		public:
			virtual ~Listener() {}
			virtual void onValue(Output *pOutput, real value) = 0;
		};

		// Constructors and destructors
		Output(bool analog = true);
		virtual ~Output();

		// Connection
		Connection *getConnection() const { return m_pConnection; }
		bool isConnected() const { return (m_pConnection != 0); }

		// Information
		bool isAnalog() const { return m_analog; }
		real getCurrentValue() const { return m_value; }

		// Other functions
		void sendValue(real value);
		void sendMinValue() { sendValue(0); }
		void sendMaxValue() { sendValue(1); }

		// Listeners
		void addListener(Listener *pListener);
		void removeListener(Listener *pListener);

	protected:
		/// The current value
		real m_value;

		/// The connected input
		Connection *m_pConnection;
		
		friend class Connection;
		void setConnection(Connection *pConnection) { m_pConnection = pConnection; }

		/** If this is true, a value will be send between 0 and 1.
			Otherwise, there will be toggled between 0 and 1.
			@note This is just a hint that this output exposes (for example for widgets,
			so they can choose to visualize the output as a slider or a button).
		*/
		bool m_analog;

		// Listeners
		typedef std::set<Listener *>ListenerSet;
		ListenerSet m_listeners;
	};
}

#endif // MIDIME_OUTPUT_H
