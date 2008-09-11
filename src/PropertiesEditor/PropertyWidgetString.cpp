// Includes
#include "PropertyWidgetString.h"
#include <Properties/StandardProperties.h>
#include <QtGui/QLineEdit>
#include <QtGui/QGridLayout>

using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

PropertyWidgetString::PropertyWidgetString(Property *pProperty, QWidget *parent)
: PropertyWidget(pProperty, parent)
{
	m_pLineEdit = new QLineEdit(this);
	m_pLayout->addWidget(m_pLineEdit);
	
	m_pLineEdit->setText(static_cast<StringProperty *>(m_pProperty)->getValue().c_str());
	
	connect(m_pLineEdit, SIGNAL(editingFinished()), SLOT(changed()));
}

PropertyWidgetString::~PropertyWidgetString()
{
}


/******************
* Other functions *
******************/

void PropertyWidgetString::updateFromProperty()
{
	StringProperty *pString = static_cast<StringProperty *>(m_pProperty);
	
	if (pString->getValue().c_str() != m_pLineEdit->text())
		m_pLineEdit->setText(pString->getValue().c_str());
}


/**********************
* Protected functions *
**********************/

void PropertyWidgetString::changed()
{
	QString text = m_pLineEdit->text().trimmed();
	if (m_prevValue == text)
		return;

	string value = text.toStdString();
	static_cast<StringProperty *>(m_pProperty)->setValue(value);
	m_prevValue = text;
}
