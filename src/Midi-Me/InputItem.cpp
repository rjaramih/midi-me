// Includes
#include "InputItem.h"
#include "OutputItem.h"
#include "EdgeItem.h"
#include "ChainWidget.h"
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
}

InputItem::~InputItem()
{
	m_pInput->removeListener(this);
}

/******************
* Other functions *
******************/

void InputItem::disconnect()
{
	if(!m_pConnectedEdge)
		return;

	// The output is in charge of connections
	m_pConnectedEdge->getOutputItem()->disconnect();
}

void InputItem::onValue(Input *pInput, real value)
{
	real u = value;
	float meterWidth = value * width;

	m_pMeterItem->setRect(0, 0, meterWidth, height);
}

void InputItem::showSettings(QPoint &position)
{
	// Generate the context menu
	QMenu *pMenu = new QMenu(m_pChainWidget);

	QAction *pInverted = pMenu->addAction("Inverted");
	pInverted->setCheckable(true);
	pInverted->setChecked(m_pInput->isInverted());
	connect(pInverted, SIGNAL(triggered(bool)), SLOT(setInverted(bool)));

	pMenu->popup(position);
}

void InputItem::setInverted(bool inverted)
{
	m_pInput->setInverted(inverted);
}


/**********************
* Protected functions *
**********************/

void InputItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *pEvent)
{
	if(pEvent->button() == Qt::RightButton && m_pChainWidget->getState() == ChainWidget::State_Normal)
		showSettings(pEvent->screenPos());
}
