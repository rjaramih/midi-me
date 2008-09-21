// Includes
#include "ChainEnd.h"
#include "MidiOutput.h"
using namespace MidiMe;

#include <Properties/StandardProperties.h>


/******************************
* Constructors and destructor *
******************************/

ChainEnd::ChainEnd(MidiOutput *pMidi, Input *pInput)
: m_pMidi(pMidi), m_pInput(pInput)
{
	assert(m_pMidi && m_pInput);
	createProperties();
}

ChainEnd::~ChainEnd()
{
	destroyProperties();
}


/******************
* Other functions *
******************/


/**********************
* Protected functions *
**********************/

unsigned int ChainEnd::getMidiPort() const
{
	return m_pMidi->getOpenedPort();
}

//! @todo Support multiple opened midi ports
void ChainEnd::setMidiPort(unsigned int port)
{
	if(m_pMidi->isOpened())
	{
		if(m_pMidi->getOpenedPort() != port)
		{
			cerr << "[ChainEnd] Warning: opening new midi port " << port << ". Closing old one!" << endl;
			if(!(m_pMidi->close() && m_pMidi->open(port)))
				cerr << "[ChainEnd] Error opening midi port " << port << "!" << endl;
		}
	}
	else
	{
		if(!m_pMidi->open(port))
			cerr << "[ChainEnd] Error opening midi port " << port << "!" << endl;
	}
}

int ChainEnd::getCC() const
{
	//return m_pMidi->
	return 0;
}

void ChainEnd::setCC(int channel)
{
}

void ChainEnd::createProperties()
{
	// Add the properties
	UIntProperty::GetFunctor portGetter = fastdelegate::MakeDelegate(this, &ChainEnd::getMidiPort);
	UIntProperty::SetFunctor portSetter = fastdelegate::MakeDelegate(this, &ChainEnd::setMidiPort);
	UIntProperty *pPort = new UIntProperty("Midi port", portGetter, portSetter);
}

void ChainEnd::destroyProperties()
{
	// Destroy all properties
	const PropertyList &props = getPropertiesList();
	for(PropertyList::const_iterator it = props.begin(); it != props.end(); ++it)
		delete *it;
	clearProperties();
}
