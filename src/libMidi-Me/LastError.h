#ifndef MIDIME_LASTERROR_H
#define MIDIME_LASTERROR_H

// Includes
#include "global.h"

namespace MidiMe
{
	// Forward declarations

	/** Classes derived from LastError hold a mutable last error string,
		which can be set, typically by functions that return false on error.
		Because the value is mutable, you can also set the last error in a const function
	*/
	class LIBMIDIME_API LastError
	{
	public:
		virtual ~LastError() {}
		const string &getLastError() const { return m_lastError; }
    
	protected:
		void setLastError(const string &error) const { m_lastError = error; }
		mutable string m_lastError;
	};
}

#endif // MIDIME_LASTERROR_H
