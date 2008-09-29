// Includes
#include "ChainEnd.h"
#include "MidiOutput.h"
#include "Connection.h"
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

bool ChainEnd::isInverted() const
{
	if(m_pInput->isConnected())
		return m_pInput->getConnection()->isInverted();

	return false;
}

void ChainEnd::setInverted(bool inverted)
{
	if(m_pInput->isConnected())
		m_pInput->getConnection()->setInverted(inverted);
}


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
	UIntProperty *pProperty = new UIntProperty("Channel", valueGetter, valueSetter);
	addProperty(pProperty);

	// Controller
	valueGetter = fastdelegate::MakeDelegate(this, &ChainEnd::getController);
	valueSetter = fastdelegate::MakeDelegate(this, &ChainEnd::setController);
	pProperty = new UIntProperty("Controller", valueGetter, valueSetter);
	addProperty(pProperty);

	// Starting value
	valueGetter = fastdelegate::MakeDelegate(this, &ChainEnd::getStartValue);
	valueSetter = fastdelegate::MakeDelegate(this, &ChainEnd::setStartValue);
	pProperty = new UIntProperty("Starting value", valueGetter, valueSetter);
	addProperty(pProperty);

	// Ending value
	valueGetter = fastdelegate::MakeDelegate(this, &ChainEnd::getEndValue);
	valueSetter = fastdelegate::MakeDelegate(this, &ChainEnd::setEndValue);
	pProperty = new UIntProperty("Ending value", valueGetter, valueSetter);
	addProperty(pProperty);

	// TEMP: inverted
	BoolProperty::SetFunctor invSetter = fastdelegate::MakeDelegate(this, &ChainEnd::setInverted);
	BoolProperty::GetFunctor invGetter = fastdelegate::MakeDelegate(this, &ChainEnd::isInverted);
	BoolProperty *pInvProperty = new BoolProperty("Inverted", invGetter, invSetter);
	addProperty(pInvProperty);
}

void ChainEnd::destroyProperties()
{
	// Note: We copy this list so we can call clearProperties and inform the listeners
	const PropertyList props = m_propertiesList;
	clearProperties();

	// Destroy all properties
	for(PropertyList::const_iterator it = props.begin(); it != props.end(); ++it)
		delete *it;
}
