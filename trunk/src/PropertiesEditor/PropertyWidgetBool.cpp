// Includes
#include "PropertyWidgetBool.h"
#include <Properties/StandardProperties.h>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>

using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

PropertyWidgetBool::PropertyWidgetBool(Property *pProperty, QWidget *parent)
: PropertyWidget(pProperty, parent)
{
	m_pCheckBox = new QCheckBox(this);
	m_pLayout->addWidget(m_pCheckBox);
	
	if (static_cast<BoolProperty *>(m_pProperty)->getValue())
		m_pCheckBox->setCheckState(Qt::Checked);
	
	connect(m_pCheckBox, SIGNAL(stateChanged(int)), SLOT(changed(int)));
}

PropertyWidgetBool::~PropertyWidgetBool()
{
}


/******************
* Other functions *
******************/

void PropertyWidgetBool::updateFromProperty()
{
	BoolProperty *pBool = static_cast<BoolProperty *>(m_pProperty);
	Qt::CheckState state = pBool->getValue() ? Qt::Checked : Qt::Unchecked;

	if (state != m_pCheckBox->checkState())
		m_pCheckBox->setCheckState(state);
}


/**********************
* Protected functions *
**********************/

void PropertyWidgetBool::changed(int state)
{
	static_cast<BoolProperty *>(m_pProperty)->setValue(state == Qt::Checked);
}
