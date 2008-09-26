// Includes
#include "MidiOutput.h"
using namespace MidiMe;

#include <RtMidi/RtMidi.h>


/******************************
* Constructors and destructor *
******************************/

MidiOutput::MidiOutput()
: m_pMidiOut(0), m_opened(false), m_midiPort(0)
{
	initMidi();
}

MidiOutput::~MidiOutput()
{
	destroyMidi();
}


/******************
* Other functions *
******************/

unsigned int MidiOutput::numPorts() const
{
	return m_pMidiOut->getPortCount();
}

string MidiOutput::getPortName(unsigned int port) const
{
	return m_pMidiOut->getPortName(port);
}

bool MidiOutput::open(unsigned int midiPort)
{
	if(m_opened)
	{
		setLastError("Already opened");
		return false;
	}

	try
	{
		m_midiPort = midiPort;
		m_pMidiOut->openPort(m_midiPort);
	}
	catch(RtError &error)
	{
		setLastError("Error opening port: " + error.getMessage());
		return false;
	}

	m_opened = true;
	return true;
}

bool MidiOutput::close()
{
	if(!m_opened)
	{
		setLastError("Not opened");
		return false;
	}

	try
	{
		m_pMidiOut->closePort();
	}
	catch(RtError &error)
	{
		setLastError("Error closing port: " + error.getMessage());
		return false;
	}

	m_opened = false;
	return true;
}

bool MidiOutput::sendControllerMessage(unsigned int channel, unsigned int controller, unsigned int value)
{
	std::vector<unsigned char> message;
	message.push_back(176 + channel); // "Controller" + channel
	message.push_back(controller); // Controller ID
	message.push_back(value); // Value

	try
	{
		//cerr << "[MidiOutput::DEBUG] Sending controller " << controller << " value " << value << endl;
		m_pMidiOut->sendMessage(&message);
	}
	catch(RtError &error)
	{
		setLastError("Midi error: " + error.getMessage());
		return false;
	}

	return true;
}


/**********************
* Protected functions *
**********************/

bool MidiOutput::initMidi()
{
	try
	{
		m_pMidiOut = new RtMidiOut();
	}
	catch(RtError &error)
	{
		setLastError("RtMidiOut error: " + error.getMessage());
		return false;
	}

	return true;
}

bool MidiOutput::destroyMidi()
{
	try
	{
		if(m_opened)
			m_pMidiOut->closePort();

		delete m_pMidiOut;
		m_pMidiOut = 0;
	}
	catch(RtError &error)
	{
		setLastError("RtMidiOut error: " + error.getMessage());
		return false;
	}
	
	return true;
}
