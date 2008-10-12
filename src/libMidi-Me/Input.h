#ifndef MIDIME_INPUT_H
#define MIDIME_INPUT_H

// Includes
#include "global.h"
#include <set>

namespace MidiMe
{
	// Forward declarations
	class Connection;

	/** This class represents an input to connect an output with.
		An input has a mininum and maximum value.
		
		The input will automatically map the incoming value from an output between the minimum and maximum
		value of this input when sending the value to the listeners.
	*/
	class LIBMIDIME_API Input
	{
	public:
		class Listener
		{
		public:
			virtual ~Listener() {}
			virtual void onValue(Input *pInput, real value) = 0;
		};

		// Constructors and destructors
		Input();
		virtual ~Input();

		// Information
		real getCurrentValue() const { return m_value; }

		// Short info message
		const string &getInfo() const { return m_info; }
		void setInfo(const string &info) { m_info = info; }

		// Connection
		Connection *getConnection() const { return m_pConnection; }
		bool isConnected() const { return (m_pConnection != 0); }

		// Listeners
		void addListener(Listener *pListener);
		void removeListener(Listener *pListener);

	protected:
		/// The (optional) short info text
		string m_info;

		/// The current value
		real m_value;

		/// The connected output
		Connection *m_pConnection;

		friend class Connection;
		void setConnection(Connection *pConnection) { m_pConnection = pConnection; }
		void processValue(real value);

		// Listeners
		typedef std::set<Listener *>ListenerSet;
		ListenerSet m_listeners;
	};
}

#endif // MIDIME_INPUT_H
