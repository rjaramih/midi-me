#ifndef MIDIME_CONVERTER_H
#define MIDIME_CONVERTER_H

// Includes
#include "global.h"

namespace MidiMe
{
	// Forward declarations
	class ConverterManager;

	/** Class Description */
	class Converter
	{
	public:
		// Constructors and destructor
		Converter(ConverterManager *pManager);
		virtual ~Converter();

		// Information
		ConverterManager *getManager() const { return m_pManager; }
    
	protected:
		// Member variables
		ConverterManager *m_pManager;
	};
}

#endif // MIDIME_CONVERTER_H
