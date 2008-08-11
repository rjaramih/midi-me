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
: QGraphicsRectItem(pParent), m_pOutput(pOutput), m_pMeterItem(0)
{
	assert(m_pOutput);

	// Setup item
	setFlag(ItemIsSelectable);
	//setFlag(ItemIsMovable);
	//setFlag(ItemIsFocusable);
	setRect(0,0, g_width, g_height);
	setBrush(Qt::NoBrush);

	// Create the meter item
	m_pMeterItem = new QGraphicsRectItem(this);
	m_pMeterItem->setBrush(Qt::green);
	m_pMeterItem->setRect(0, 0, 0, g_height);

	m_pOutput->addListener(this);
}

OutputItem::~OutputItem()
{
	delete m_pMeterItem;

	m_pOutput->removeListener(this);
}

void OutputItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *pEvent)
{
	return QGraphicsRectItem::contextMenuEvent(pEvent);
}

QVariant OutputItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
	return QGraphicsRectItem::itemChange(change, value);
}

void OutputItem::onValue(Output *pOutput, int value)
{
	float u = (value - pOutput->getMinValue()) / (float) (pOutput->getMaxValue() - pOutput->getMinValue());
	float width = u * g_width;

	m_pMeterItem->setRect(0, 0, width, g_height);
}
