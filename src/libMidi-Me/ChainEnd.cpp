// Includes
#include "ChainEnd.h"
#include "MidiOutput.h"
using namespace MidiMe;

#include <Properties/StandardProperties.h>


/******************************
* Constructors and destructor *
******************************/

ChainEnd::ChainEnd(MidiOutput *pMidi)
: m_pMidi(pMidi), m_pInput(0)
, m_channel(0), m_controller(0), m_startValue(0), m_endValue(128)
{
	assert(m_pMidi);
	m_pInput = new Input();
	m_pInput->addListener(this);

	createProperties();
}

ChainEnd::~ChainEnd()
{
	destroyProperties();
	delete m_pInput;
}


/******************
* Other functions *
******************/


/**********************
* Protected functions *
**********************/

void ChainEnd::onValue(Input *pInput, real value)
{
	assert(pInput == m_pInput);

	// Map the value
	int diffOutput = m_endValue - m_startValue;
	int outValue = (int) (m_startValue + diffOutput * value);

	// Send the CC message
	m_pMidi->sendControllerMessage(m_channel, m_controller, outValue);
}

void ChainEnd::createProperties()
{
	// Channel
	UIntProperty::GetFunctor valueGetter = fastdelegate::MakeDelegate(this, &ChainEnd::getChannel);
	UIntProperty::SetFunctor valueSetter = fastdelegate::MakeDelegate(this, &ChainEnd::setChannel);
	UIntProperty *pProperty = new UIntProperty(this, "Channel", valueGetter, valueSetter);

	// Controller
	valueGetter = fastdelegate::MakeDelegate(this, &ChainEnd::getController);
	valueSetter = fastdelegate::MakeDelegate(this, &ChainEnd::setController);
	pProperty = new UIntProperty(this, "Controller", valueGetter, valueSetter);

	// Starting value
	valueGetter = fastdelegate::MakeDelegate(this, &ChainEnd::getStartValue);
	valueSetter = fastdelegate::MakeDelegate(this, &ChainEnd::setStartValue);
	pProperty = new UIntProperty(this, "Starting value", valueGetter, valueSetter);

	// Ending value
	valueGetter = fastdelegate::MakeDelegate(this, &ChainEnd::getEndValue);
	valueSetter = fastdelegate::MakeDelegate(this, &ChainEnd::setEndValue);
	pProperty = new UIntProperty(this, "Ending value", valueGetter, valueSetter);
}

void ChainEnd::destroyProperties()
{
	// Destroy all properties
	while(!m_propertiesList.empty())
		delete m_propertiesList.front();
}
