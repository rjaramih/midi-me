// Includes
#include "ChainStart.h"
using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

ChainStart::ChainStart(Output *pOutput)
: /*m_pDevice(0),*/ m_pOutput(pOutput)
{
	assert(m_pOutput);
}

ChainStart::~ChainStart()
{
}


/******************
* Other functions *
******************/

/*void ChainStart::setDevice(InputDevice *pDevice)
{
	if(m_pDevice == pDevice)
		return;

	InputDevice *pOldDevice = m_pDevice;
	m_pDevice = pDevice;

	fireDeviceChanged(pOldDevice);
}

void ChainStart::setOutput(Output *pOutput)
{
	if(m_pOutput == pOutput)
		return;

	Output *pOldOutput = m_pOutput;
	m_pOutput = pOutput;

	fireOutputChanged(pOldOutput);
}

void ChainStart::addListener(Listener *pListener)
{
	m_listeners.insert(pListener);
}

void ChainStart::removeListener(Listener *pListener)
{
	m_listeners.erase(pListener);
}*/


/**********************
* Protected functions *
**********************/

/*void ChainStart::fireDeviceChanged(InputDevice *pOldDevice)
{
	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onDeviceChanged(m_pDevice, pOldDevice);
}

void ChainStart::fireOutputChanged(Output *pOldOutput)
{
	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onOutputChanged(m_pOutput, pOldOutput);
}*/
