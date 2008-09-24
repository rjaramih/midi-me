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

ChainStartItem::ChainStartItem(ChainWidget *pChainWidget, ChainStart *pChainStart)
: OutputItem(pChainWidget, pChainStart->getOutput()), m_pChainStart(pChainStart)
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

/** Adjust the current position so it fits the viewport */
void ChainStartItem::adjustPosition()
{
	QPointF position = pos();
	adjustPosition(position);
	setPos(position);
}


/**********************
* Protected functions *
**********************/

void ChainStartItem::mousePressEvent(QGraphicsSceneMouseEvent *pEvent)
{
	// Show properties on selection
	/*if(m_pPropertyEditor)
	{
		m_pPropertyEditor->clear();
		m_pPropertyEditor->addCollection(m_p->getType(), "Processor", m_pProcessor);
	}*/
	
	return OutputItem::mousePressEvent(pEvent);
}

QVariant ChainStartItem::itemChange(GraphicsItemChange change, const QVariant &value)
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

	return OutputItem::itemChange(change, value);
}

void ChainStartItem::adjustPosition(QPointF &position)
{
	assert(scene() && scene()->views().size() == 1);
	QGraphicsView *pView = scene()->views().first();

	// Make sure the item stays at the left edge
	position.setX(-1.0f);

	// Make sure the item stays in the visible scene
	float maxY = pView->sceneRect().bottom() - rect().height() - g_margin;
	float posY = position.y();
	if(position.y() < g_margin)
		position.setY(g_margin);
	if(position.y() > maxY)
		position.setY(maxY);
}
