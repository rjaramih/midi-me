// Includes
#include "PropertyWidgetCompound.h"
#include <Properties/StandardProperties.h>
#include <QtGui/QLabel>
#include <QtGui/QGridLayout>

using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

PropertyWidgetCompound::PropertyWidgetCompound(Property *pProperty, QWidget *parent)
: PropertyWidget(pProperty, parent)
{
	m_pLabel = new QLabel(this);
	m_pLayout->addWidget(m_pLabel);
	
	m_pLabel->setText(static_cast<CompoundProperty *>(m_pProperty)->toString().c_str());
}

PropertyWidgetCompound::~PropertyWidgetCompound()
{
}


/******************
* Other functions *
******************/

void PropertyWidgetCompound::updateFromProperty()
{
	m_pLabel->setText(static_cast<CompoundProperty *>(m_pProperty)->toString().c_str());
}


/**********************
* Protected functions *
**********************/

void PropertyWidgetCompound::changed()
{
}
