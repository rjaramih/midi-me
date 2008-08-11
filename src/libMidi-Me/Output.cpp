// Includes
#include "Output.h"
using namespace MidiMe;

/******************************
* Constructors and destructor *
******************************/

Output::Output(int minValue, int maxValue, bool analog)
: m_pInput(0), m_minValue(minValue), m_maxValue(maxValue), m_analog(analog)
{
}

Output::~Output()
{
}


/******************
* Other functions *
******************/

void Output::sendValue(int value)
{
	if(isConnected())
		m_pInput->processValue(value);
}
