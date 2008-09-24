// Includes
#include "Midi-MeProperties.h"
#include "Input.h"
#include <Properties/StringUtil.h>
using namespace MidiMe;


// Static variables
string InputValueProperty::type("InputValue");


/*********************
* InputValueProperty *
*********************/

InputValueProperty::InputValueProperty(const string &name, const GetFunctor &getter, const SetFunctor &setter, Input *pInput)
: GenericProperty<real>(name, getter, setter), m_pInput(pInput)
{
	assert(m_pInput);
}

InputValueProperty::~InputValueProperty()
{
}

string InputValueProperty::toString() const
{
	return StringUtil::toString(getValue());
}

void InputValueProperty::fromString(const string &value)
{
	setValue(StringUtil::toFloat(value));
}

/** Set the value of this property to the current value of the associated input. */
void InputValueProperty::setFromInput()
{
	setValue(m_pInput->getCurrentValue());
}
