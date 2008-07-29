#ifndef MIDIME_AXISCONVERTER_H
#define MIDIME_AXISCONVERTER_H

// Includes
#include "global.h"
#include "Converter.h"
#include <list>

namespace MidiMe
{
	// Forward declarations

	/** Class Description */
	class AxisConverter: public Converter
	{
	public:
		/// One slice of the axis
		struct Slice
		{
			int minValue, maxValue;
			int beginOutputValue, endOutputValue;
			unsigned int channel, controller;

			Slice(): minValue(0), maxValue(100), beginOutputValue(0), endOutputValue(128)
				, channel(0), controller(0) {}
		};

		// Constructors and destructor
		AxisConverter(ConverterManager *pManager, int axis);
		virtual ~AxisConverter();

		// Information
		int getAxis() const { return m_axis; }

		// Other functions
		bool addSlice(const Slice &slice);
		bool processValue(int value);

	protected:
		// Protected functions
		Slice *getSlice(int value);

		// Member variables
		int m_axis; //!< The OIS JoyStick axis used

		typedef std::list<Slice> SliceList;
		SliceList m_slices;
	};
}

#endif // MIDIME_AXISCONVERTER_H
