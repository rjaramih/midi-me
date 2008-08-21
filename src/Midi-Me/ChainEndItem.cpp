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

ChainEndItem::ChainEndItem(ChainEnd *pChainEnd, QGraphicsItem *pParent)
: InputItem(pChainEnd->getInput(), pParent), m_pChainEnd(pChainEnd)
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


/**********************
* Protected functions *
**********************/

void ChainEndItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *pEvent)
{
	return InputItem::contextMenuEvent(pEvent);
}

QVariant ChainEndItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if(change == ItemPositionChange)
	{
		assert(scene() && scene()->views().size() == 1);
		QGraphicsView *pView = scene()->views().first();

		QPointF pos = value.toPointF();

		// Make sure the item stays at the right edge
		pos.setX(pView->sceneRect().right() - rect().width() + 1.0f);

		// Make sure the item stays in the visible scene
		float maxY = pView->sceneRect().bottom() - rect().height() - g_margin;
		float posY = pos.y();
		if(pos.y() < 0.0f)
			pos.setY(0.0f);
		if(pos.y() > maxY)
			pos.setY(maxY);

		return pos;
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
