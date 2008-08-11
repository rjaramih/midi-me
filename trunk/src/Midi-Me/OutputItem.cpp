// Includes
#include "OutputItem.h"
using namespace MidiMe;

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>


/// The hardcoded margin between items
static const float g_margin(5.0f);
static const float g_width(50.0f);
static const float g_height(15.0f);


/************
* OutputItem *
************/

OutputItem::OutputItem(Output *pOutput, QGraphicsItem *pParent)
: QGraphicsRectItem(pParent), m_pOutput(pOutput)
{
	assert(m_pOutput);

	// Setup item
	setFlag(ItemIsSelectable);
	//setFlag(ItemIsMovable);
	//setFlag(ItemIsFocusable);

	setRect(0,0, g_width, g_height);
}

OutputItem::~OutputItem()
{
}

void OutputItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *pEvent)
{
	return QGraphicsRectItem::contextMenuEvent(pEvent);
}

QVariant OutputItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
	return QGraphicsRectItem::itemChange(change, value);
}
