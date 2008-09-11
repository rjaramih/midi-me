// Includes
#include "PropertyWidgetInt.h"
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

PropertyWidgetInt::PropertyWidgetInt(Property *pProperty, QWidget *parent)
: PropertyWidget(pProperty, parent)
{
	m_pSpinBox = new QSpinBox(this);
	m_pLayout->addWidget(m_pSpinBox);
	
	m_pSpinBox->setRange(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
	m_pSpinBox->setValue(static_cast<IntProperty *>(m_pProperty)->getValue());
	
	connect(m_pSpinBox, SIGNAL(valueChanged(int)), SLOT(changed(int)));
}

PropertyWidgetInt::~PropertyWidgetInt()
{
}


/******************
* Other functions *
******************/

void PropertyWidgetInt::updateFromProperty()
{
	IntProperty *pInt = static_cast<IntProperty *>(m_pProperty);

	if (pInt->getValue() != m_pSpinBox->value())
		m_pSpinBox->setValue(pInt->getValue());
}


/**********************
* Protected functions *
**********************/

void PropertyWidgetInt::changed(int value)
{
	static_cast<IntProperty *>(m_pProperty)->setValue(value);
}
