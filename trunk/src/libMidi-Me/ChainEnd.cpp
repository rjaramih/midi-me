// Includes
#include "ChainEnd.h"
using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

ChainEnd::ChainEnd()
: m_pMidi(0), m_pInput(0)
{
}

ChainEnd::~ChainEnd()
{
}


/******************
* Other functions *
******************/

void ChainEnd::setMidi(MidiOutput *pMidi)
{
	if(m_pMidi == pMidi)
		return;

	MidiOutput *pOldMidi = m_pMidi;
	m_pMidi = pMidi;

	fireMidiChanged(pOldMidi);
}

void ChainEnd::setInput(Input *pInput)
{
	if(m_pInput == pInput)
		return;

	Input *pOldInput = m_pInput;
	m_pInput = pInput;

	fireInputChanged(pOldInput);
}

void ChainEnd::addListener(Listener *pListener)
{
	m_listeners.insert(pListener);
}

void ChainEnd::removeListener(Listener *pListener)
{
	m_listeners.erase(pListener);
}


/**********************
* Protected functions *
**********************/

void ChainEnd::fireMidiChanged(MidiOutput *pOldMidi)
{
	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onMidiChanged(m_pMidi, pOldMidi);
}

void ChainEnd::fireInputChanged(Input *pOldInput)
{
	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onInputChanged(m_pInput, pOldInput);
}
