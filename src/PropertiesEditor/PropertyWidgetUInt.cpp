// Includes
#include "PropertyWidgetUInt.h"
#include <Properties/StandardProperties.h>
#include <QtGui/QSpinBox>
#include <QtGui/QGridLayout>
#include <limits>

using namespace MidiMe;

#ifdef max
#	undef max
#endif
#ifdef min
#	undef min
#endif


/******************************
* Constructors and destructor *
******************************/

PropertyWidgetUInt::PropertyWidgetUInt(Property *pProperty, QWidget *parent)
: PropertyWidget(pProperty, parent)
{
	m_pSpinBox = new QSpinBox(this);
	m_pLayout->addWidget(m_pSpinBox);
	
	m_pSpinBox->setMinimum(0);
	//! @todo Add min and max values as settings
	m_pSpinBox->setMaximum(256);
	m_pSpinBox->setValue(static_cast<UIntProperty *>(m_pProperty)->getValue());
	
	connect(m_pSpinBox, SIGNAL(valueChanged(int)), SLOT(changed(int)));
}

PropertyWidgetUInt::~PropertyWidgetUInt()
{
}


/******************
* Other functions *
******************/

void PropertyWidgetUInt::updateFromProperty()
{
	UIntProperty *pUInt = static_cast<UIntProperty *>(m_pProperty);

	if (pUInt->getValue() != m_pSpinBox->value())
		m_pSpinBox->setValue(pUInt->getValue());
}


/**********************
* Protected functions *
**********************/

void PropertyWidgetUInt::changed(int value)
{
	static_cast<UIntProperty *>(m_pProperty)->setValue(value);
}
