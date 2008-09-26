// Includes
#include "PropertyWidget.h"
#include <QtGui/QHBoxLayout>
using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

PropertyWidget::PropertyWidget(Property *pProperty, QWidget *parent)
: QWidget(parent)
{
	m_pLayout = new QHBoxLayout(this);
	m_pProperty = pProperty;
	m_modified = false;
	
	m_pLayout->setMargin(0);
	setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

	//m_pProperty->addListener(this);
}

PropertyWidget::~PropertyWidget()
{
	//m_pProperty->removeListener(this);
}
