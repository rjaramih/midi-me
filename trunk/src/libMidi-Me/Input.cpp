// Includes
#include "Input.h"
using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

Input::Input()
: m_value(0), m_pConnection(0)
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

void Input::processValue(real value)
{
	// This should only be called by a connected output
	assert(isConnected());

	m_value = value;

	// Send to connected listeners
	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onValue(this, m_value);
}
