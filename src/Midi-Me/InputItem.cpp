// Includes
#include "InputItem.h"
using namespace MidiMe;

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>


/// The hardcoded margin between items
static const float g_margin(5.0f);
static const float g_width(50.0f);
static const float g_height(15.0f);


/************
* InputItem *
************/

InputItem::InputItem(Input *pInput, QGraphicsItem *pParent)
: QGraphicsRectItem(pParent), m_pInput(pInput)
{
	assert(m_pInput);

	// Setup item
	setFlag(ItemIsSelectable);
	//setFlag(ItemIsMovable);
	//setFlag(ItemIsFocusable);

	setRect(0,0, g_width, g_height);
}

InputItem::~InputItem()
{
}

void InputItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *pEvent)
{
	return QGraphicsRectItem::contextMenuEvent(pEvent);
}

QVariant InputItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
	return QGraphicsRectItem::itemChange(change, value);
}
