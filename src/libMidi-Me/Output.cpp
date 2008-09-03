// Includes
#include "Output.h"
using namespace MidiMe;

/******************************
* Constructors and destructor *
******************************/

Output::Output(bool analog)
: m_pInput(0), m_analog(analog)
{
}

Output::~Output()
{
}


/******************
* Other functions *
******************/

void Output::sendValue(real value)
{
	if(isConnected())
		m_pInput->processValue(value);

	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onValue(this, value);
}

void Output::addListener(Listener *pListener)
{
	m_listeners.insert(pListener);
}

void Output::removeListener(Listener *pListener)
{
	m_listeners.erase(pListener);
}
