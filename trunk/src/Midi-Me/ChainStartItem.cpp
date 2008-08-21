// Includes
#include "ChainStartItem.h"
#include "OutputItem.h"
#include <libMidi-Me/ChainStart.h>
#include <libMidi-Me/Output.h>
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

ChainStartItem::ChainStartItem(ChainStart *pChainStart, QGraphicsItem *pParent)
: OutputItem(pChainStart->getOutput(), pParent)/*QGraphicsRectItem(pParent)*/, m_pChainStart(pChainStart)/*, m_pOutputItem(0)*/
{
	assert(m_pChainStart);

	// Setup item
	//setFlag(ItemIsSelectable);
	setFlag(ItemIsMovable);
	//setFlag(ItemIsFocusable);

	QString toolTip = m_pChainStart->getDevice()->getName().c_str();
	toolTip += QString("\nOutput %1").arg(m_pChainStart->getOutputID());
	
	Output *pOutput = m_pChainStart->getOutput();
	if(pOutput->isAnalog())
		toolTip += " (analog)";
	else
		toolTip += " (digital)";

	setToolTip(toolTip);
}

ChainStartItem::~ChainStartItem()
{
}


/******************
* Other functions *
******************/


/**********************
* Protected functions *
**********************/

void ChainStartItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *pEvent)
{
	return OutputItem::contextMenuEvent(pEvent);
}

QVariant ChainStartItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if(change == ItemPositionChange)
	{
		assert(scene() && scene()->views().size() == 1);
		QGraphicsView *pView = scene()->views().first();

		QPointF pos = value.toPointF();

		// Make sure the item stays at the left edge
		pos.setX(-1.0f);

		// Make sure the item stays in the visible scene
		float maxY = pView->sceneRect().bottom() - rect().height() - g_margin;
		float posY = pos.y();
		if(pos.y() < 0.0f)
			pos.setY(0.0f);
		if(pos.y() > maxY)
			pos.setY(maxY);

		// Make sure the item doesn't collide with another item
		/*QList<QGraphicsItem *> coll = collidingItems();
		if(!coll.empty())
			return this->pos();*/

		return pos;
	}

	return OutputItem::itemChange(change, value);
}
