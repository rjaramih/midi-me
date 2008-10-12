#ifndef MIDIME_CONNECTION_H
#define MIDIME_CONNECTION_H

// Includes
#include "global.h"
#include <Properties/PropertyCollection.h>

namespace MidiMe
{
	// Forward declarations
	class Input;
	class Output;

	/** A connection contains all information that connects an output to an input.
	*/
	class LIBMIDIME_API Connection: public PropertyCollection
	{
	public:
		// Constructors and destructor
		Connection(Input *pInput, Output *pOutput);
		virtual ~Connection();

		// Information
		Input *getInput() const { return m_pInput; }
		Output *getOutput() const { return m_pOutput; }

		// Other functions
		void processValue(real value);
    
	protected:
		// Member variables
		Input *m_pInput;
		Output *m_pOutput;
	};
}

#endif // MIDIME_CONNECTION_H
