#ifndef MIDIME_CLASSNAME_H
#define MIDIME_CLASSNAME_H

// Includes
#include "global.h"

namespace MidiMe
{
	// Forward declarations

	/** Singleton class description */
	class PROJECTNAME_API ClassName
	{
	protected:
		// Member variables

	private:
		// Private constructors and destructor
		ClassName();
		ClassName(const ClassName &source); //!< Copy constructor, not implemented
		virtual ~ClassName();

		//! Private assignment operator, not implemented
		ClassName &operator =(const ClassName &source);

	public:
		// Singleton function
		static ClassName &getInstance();

		// Get functions

		// Set functions

		// Other functions
	};
}

#endif // MIDIME_CLASSNAME_H
