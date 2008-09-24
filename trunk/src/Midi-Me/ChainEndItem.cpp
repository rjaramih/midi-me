// Includes
#include "ChainEndItem.h"
#include "InputItem.h"
#include <libMidi-Me/ChainEnd.h>
#include <libMidi-Me/Input.h>
#include <libMidi-Me/DeviceManager.h>
#include <libMidi-Me/InputDevice.h>
using namespace MidiMe;

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>
#include <QtGui/QMenu>
#include <QtGui/QGraphicsSceneContextMenuEvent>


/// The hardcoded margin between items
static const float g_margin(5.0f);
static const float g_stdWidth(50.0f);
static const float g_stdHeight(15.0f);


/******************************
* Constructors and destructor *
******************************/

ChainEndItem::ChainEndItem(ChainWidget *pChainWidget, ChainEnd *pChainEnd, QGraphicsItem *pParent)
: InputItem(pChainWidget, pChainEnd->getInput(), pParent), m_pChainEnd(pChainEnd)
{
	assert(m_pChainEnd);

	// Setup item
	//setFlag(ItemIsSelectable);
	setFlag(ItemIsMovable);
	//setFlag(ItemIsFocusable);
}

ChainEndItem::~ChainEndItem()
{
}


/******************
* Other functions *
******************/

/** Adjust the current position so it fits the viewport */
void ChainEndItem::adjustPosition()
{
	QPointF position = pos();
	adjustPosition(position);
	setPos(position);
}


/**********************
* Protected functions *
**********************/

void ChainEndItem::mousePressEvent(QGraphicsSceneMouseEvent *pEvent)
{
	// Show properties on selection
	/*if(m_pPropertyEditor)
	{
		m_pPropertyEditor->clear();
		m_pPropertyEditor->addCollection(m_p->getType(), "Processor", m_pProcessor);
	}*/
	
	return InputItem::mousePressEvent(pEvent);
}

QVariant ChainEndItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if(change == ItemPositionChange)
	{
		QPointF position = value.toPointF();
		adjustPosition(position);
		return position;
	}
	else if(change == ItemPositionHasChanged)
	{
		//! @todo Why is there always one colliding item?
		if(collidingItems().size() > 1)
			setBrush(Qt::red);
		else
			setBrush(Qt::NoBrush);
	}

	return InputItem::itemChange(change, value);
}

void ChainEndItem::adjustPosition(QPointF &position)
{
	assert(scene() && scene()->views().size() == 1);
	QGraphicsView *pView = scene()->views().first();

	// Make sure the item stays at the right edge
	position.setX(pView->sceneRect().right() - rect().width() + 1.0f);

	// Make sure the item stays in the visible scene
	float maxY = pView->sceneRect().bottom() - rect().height() - g_margin;
	float posY = position.y();
	if(position.y() < g_margin)
		position.setY(g_margin);
	if(position.y() > maxY)
		position.setY(maxY);
}
