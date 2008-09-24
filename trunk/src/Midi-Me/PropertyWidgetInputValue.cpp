// Includes
#include "PropertyWidgetInputValue.h"
#include <libMidi-Me/Midi-MeProperties.h>

#include <QtGui/QDoubleSpinBox>
#include <QtGui/QToolButton>
#include <QtGui/QGridLayout>

#include <limits>

using namespace MidiMe;

#ifdef max
#	undef max
#endif


/******************************
* Constructors and destructor *
******************************/

PropertyWidgetInputValue::PropertyWidgetInputValue(InputValueProperty *pProperty, QWidget *parent)
: PropertyWidget(pProperty, parent)
{
	m_pDoubleSpinBox = new QDoubleSpinBox(this);
	m_pDoubleSpinBox->setRange(0.0, 1.0);
	m_pDoubleSpinBox->setSingleStep(0.1);
	m_pDoubleSpinBox->setValue(pProperty->getValue());
	m_pLayout->addWidget(m_pDoubleSpinBox);
	connect(m_pDoubleSpinBox, SIGNAL(valueChanged(double)), SLOT(changed(double)));

	m_pSetFromInputButton = new QToolButton(this);
	m_pSetFromInputButton->setAutoRaise(true);
	m_pSetFromInputButton->setText("C");
	m_pSetFromInputButton->setToolTip("Press to use the current input value");
	m_pLayout->addWidget(m_pSetFromInputButton);
	connect(m_pSetFromInputButton, SIGNAL(clicked()), SLOT(setFromInput()));
}

PropertyWidgetInputValue::~PropertyWidgetInputValue()
{
}


/******************
* Other functions *
******************/

void PropertyWidgetInputValue::updateFromProperty()
{
	InputValueProperty *pProperty = static_cast<InputValueProperty *>(m_pProperty);

	if (pProperty->getValue() != m_pDoubleSpinBox->value())
		m_pDoubleSpinBox->setValue(pProperty->getValue());
}

void PropertyWidgetInputValue::setFromInput()
{
	InputValueProperty *pProperty = static_cast<InputValueProperty *>(m_pProperty);
	pProperty->setFromInput();
}


/**********************
* Protected functions *
**********************/

void PropertyWidgetInputValue::changed(double value)
{
	static_cast<InputValueProperty *>(m_pProperty)->setValue(value);
}


/**********
* Creator *
**********/

PropertyWidget *PropertyWidgetCreatorInputValue::createWidget(Property *pProperty)
{
	assert(pProperty->getType() == InputValueProperty::type);
	return new PropertyWidgetInputValue((InputValueProperty *) pProperty);
}

void PropertyWidgetCreatorInputValue::destroyWidget(PropertyWidget *pWidget)
{
	delete pWidget;
}
