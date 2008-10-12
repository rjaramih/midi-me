// Includes
#include "InputItem.h"
#include "OutputItem.h"
#include "ChainWidget.h"
#include "ConnectionItem.h"
using namespace MidiMe;

#include <QtGui/QGraphicsSceneMouseEvent>
#include <QtGui/QMenu>


/************
* InputItem *
************/

InputItem::InputItem(ChainWidget *pChainWidget, Input *pInput, QGraphicsItem *pParent)
: ChainItem(pChainWidget, pParent), m_pInput(pInput)
{
	assert(m_pInput);
	m_pInput->addListener(this);

	// The anchor to attach an edge to
	m_localAnchor.setX(margin);
	m_localAnchor.setY(height * 0.5f);

	// Info text
	QGraphicsTextItem *pInfo = new QGraphicsTextItem(this);
	QString html = QString("<center>") + m_pInput->getInfo().c_str() + "</center>";
	pInfo->setHtml(html);
	pInfo->setTextWidth(rect().width());
}

InputItem::~InputItem()
{
	m_pInput->removeListener(this);
}

/******************
* Other functions *
******************/

bool InputItem::isConnected() const
{
	return m_pInput->isConnected();
}

ConnectionItem *InputItem::getConnectionItem() const
{
	if(!m_pInput->isConnected())
		return 0;

	return m_pChainWidget->getConnectionItem(m_pInput->getConnection());
}

void InputItem::onValue(Input *pInput, real value)
{
	if(!m_pChainWidget->isEnabled())
		return;

	real u = value;
	float meterWidth = value * width;

	m_pMeterItem->setRect(0, 0, meterWidth, height);
}


/**********************
* Protected functions *
**********************/

QVariant InputItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if(change == ItemPositionHasChanged && m_pInput->isConnected())
		m_pChainWidget->getConnectionItem(m_pInput->getConnection())->adjust();

	return ChainItem::itemChange(change, value);
}
