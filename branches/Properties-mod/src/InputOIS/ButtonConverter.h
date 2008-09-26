#ifndef MIDIME_BUTTONCONVERTER_H
#define MIDIME_BUTTONCONVERTER_H

// Includes
#include "global.h"
#include "Converter.h"

namespace MidiMe
{
	// Forward declarations

	/** Class Description */
	class ButtonConverter: public Converter
	{
	public:
		// Constructors and destructor
		ButtonConverter(ConverterManager *pManager);
		virtual ~ButtonConverter();

		// Other functions
    
	protected:
		// Member variables
	};
}

#endif // MIDIME_BUTTONCONVERTER_H
