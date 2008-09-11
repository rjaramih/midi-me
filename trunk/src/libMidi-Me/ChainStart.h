#ifndef MIDIME_CHAINSTART_H
#define MIDIME_CHAINSTART_H

// Includes
#include "global.h"
#include <Properties/PropertyCollection.h>
#include <set>

namespace MidiMe
{
	// Forward declarations
	class InputDevice;
	class Output;

	/** Class Description */
	class LIBMIDIME_API ChainStart: public PropertyCollection
	{
	public:
		// Constructors and destructor
		ChainStart(InputDevice *pDevice, unsigned int outputID);
		virtual ~ChainStart();

		// Information
		InputDevice *getDevice() const { return m_pDevice; }
		unsigned int getOutputID() const { return m_outputID; }
		Output *getOutput() const;
    
	protected:
		// Member variables
		InputDevice *m_pDevice;
		unsigned int m_outputID;
	};
}

#endif // MIDIME_CHAINSTART_H
