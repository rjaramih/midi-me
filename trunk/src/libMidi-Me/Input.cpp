// Includes
#include "Input.h"
#include "Output.h"
using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

Input::Input(bool inverted)
: m_value(0), m_pOutput(0), m_inverted(inverted)
{
	//! @todo There has to be a better solution for indexing the in- and outputs
	static unsigned int currentID = 0;
	m_id = currentID++;
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

	// Invert if necessary
	m_value = m_inverted ? 1 - value : value;

	// Send to connected listeners
	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onValue(this, m_value);
}
