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

PropertyWidgetReal::PropertyWidgetReal(Property *pProperty, QWidget *parent)
: PropertyWidget(pProperty, parent)
{
	m_pDoubleSpinBox = new QDoubleSpinBox(this);
	m_pLayout->addWidget(m_pDoubleSpinBox);
	
	m_pDoubleSpinBox->setRange(-std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	m_pDoubleSpinBox->setValue(static_cast<RealProperty *>(m_pProperty)->getValue());
	
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

	if (pReal->getValue() != m_pDoubleSpinBox->value())
		m_pDoubleSpinBox->setValue(pReal->getValue());
}


/**********************
* Protected functions *
**********************/

void PropertyWidgetReal::changed(double value)
{
	static_cast<RealProperty *>(m_pProperty)->setValue(value);
}
