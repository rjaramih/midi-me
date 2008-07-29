// Includes
#include "AxisConverter.h"
#include "ConverterManager.h"
using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

AxisConverter::AxisConverter(ConverterManager *pManager, int axis)
: Converter(pManager), m_axis(axis)
{
}

AxisConverter::~AxisConverter()
{
}


/******************
* Other functions *
******************/

bool AxisConverter::addSlice(const Slice &slice)
{
	//! @todo Check for collisions
	m_slices.push_back(slice);
	return true;
}

bool AxisConverter::processValue(int value)
{
	Slice *pSlice = getSlice(value);
	if(!pSlice)
		return false;

	int diffInput = pSlice->maxValue - pSlice->minValue;
	int diffOutput = pSlice->endOutputValue - pSlice->beginOutputValue;
	unsigned char normValue = pSlice->beginOutputValue + diffOutput * (value - pSlice->minValue) / (diffInput);

	return m_pManager->sendControllerMessage(pSlice->channel, pSlice->controller, normValue);
}


/**********************
* Protected functions *
**********************/

AxisConverter::Slice *AxisConverter::getSlice(int value)
{
	SliceList::iterator it;
	for(it = m_slices.begin(); it != m_slices.end(); ++it)
	{
		Slice &slice = *it;

		if(slice.minValue <= value && slice.maxValue >= value)
			return &slice;
	}

	return 0;
}
