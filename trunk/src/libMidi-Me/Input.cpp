// Includes
#include "Input.h"
#include "Output.h"
using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

Input::Input(bool inverted)
: m_pOutput(0), m_inverted(inverted)
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
	if(!isConnected())
		return;

	// Invert if necessary
	real newValue = m_inverted ? 1 - value : value;

	// Send to connected listeners
	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onValue(this, newValue);
}
