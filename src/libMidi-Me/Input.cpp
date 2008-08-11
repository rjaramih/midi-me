// Includes
#include "Input.h"
#include "Output.h"
using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

Input::Input(int minValue, int maxValue, bool inverted)
: m_pOutput(0), m_minValue(minValue), m_maxValue(maxValue), m_inverted(inverted)
{
}

Input::~Input()
{
}


/******************
* Other functions *
******************/

void Input::addListener(Listener *pListener)
{
	m_listeners.insert(pListener);
}

void Input::removeListener(Listener *pListener)
{
	m_listeners.erase(pListener);
}

void Input::processValue(int value)
{
	if(!isConnected())
		return;

	int minOutput = m_pOutput->getMinValue();
	int maxOutput = m_pOutput->getMaxValue();
	int mappedValue = (int) (m_minValue + (value - minOutput) / (float) (maxOutput - minOutput) * (m_maxValue - m_minValue));

	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onValue(this, mappedValue);
}
