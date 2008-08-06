// Includes
#include "Output.h"
using namespace MidiMe;


/**************
* ValueOutput *
**************/

bool ValueOutput::sendValueStart()
{
	if(!m_pInput) return true;

	// Send through the chain
	return m_pInput->processValueStart(m_value);
}

bool ValueOutput::sendValueStop()
{
	if(!m_pInput) return true;

	// Send through the chain
	return m_pInput->processValueStop(m_value);
}


/**************
* RangeOutput *
**************/

bool RangeOutput::sendValueChanged(int value)
{
	if(value < m_minValue || value > m_maxValue) return false;
	if(!m_pInput) return true;

	// Send through the chain
	//! @todo Normalize value?
	return m_pInput->processValueChanged(value);
}
