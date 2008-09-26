// Includes
#include "PropertyWidgetReal.h"
#include <Properties/StandardProperties.h>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <limits>

using namespace MidiMe;

#ifdef max
#	undef max
#endif


/******************************
* Constructors and destructor *
******************************/

PropertyWidgetReal::PropertyWidgetReal(RealProperty *pProperty, QWidget *parent)
: PropertyWidget(pProperty, parent)
{
	m_pDoubleSpinBox = new QDoubleSpinBox(this);
	m_pDoubleSpinBox->setRange(pProperty->getMin(), pProperty->getMax());
	m_pDoubleSpinBox->setValue(pProperty->getValue());
	m_pLayout->addWidget(m_pDoubleSpinBox);
	connect(m_pDoubleSpinBox, SIGNAL(valueChanged(double)), SLOT(changed(double)));
}

PropertyWidgetReal::~PropertyWidgetReal()
{
}


/******************
* Other functions *
******************/

void PropertyWidgetReal::updateFromProperty()
{
	RealProperty *pReal = static_cast<RealProperty *>(m_pProperty);

	if(pReal->getMin() != m_pDoubleSpinBox->minimum())
		m_pDoubleSpinBox->setMinimum(pReal->getMin());

	if(pReal->getMax() != m_pDoubleSpinBox->maximum())
		m_pDoubleSpinBox->setMaximum(pReal->getMax());

	if(pReal->getValue() != m_pDoubleSpinBox->value())
		m_pDoubleSpinBox->setValue(pReal->getValue());
}


/**********************
* Protected functions *
**********************/

void PropertyWidgetReal::changed(double value)
{
	static_cast<RealProperty *>(m_pProperty)->setValue(value);
}
