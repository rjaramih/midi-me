// Includes
#include "OutputItem.h"
#include "DragData.h"
using namespace MidiMe;

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>
#include <QtCore/QMimeData>
#include <QtGui/QDrag>
#include <QtGui/QGraphicsSceneMouseEvent>

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
	//setFlag(ItemIsSelectable);
	//setFlag(ItemIsMovable);
	//setFlag(ItemIsFocusable);

	setRect(0,0, g_width, g_height);
	setBrush(Qt::NoBrush);

	// Create the meter item
	m_pMeterItem = new QGraphicsRectItem(this);
	m_pMeterItem->setBrush(Qt::green);
	m_pMeterItem->setRect(0, 0, 0, g_height);

	m_pOutput->addListener(this);

	// Enable drag-and-drop
	setAcceptDrops(true);
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

void OutputItem::mousePressEvent(QGraphicsSceneMouseEvent *pEvent)
{
	// Start drag-and-drop on right mouse click
	if(pEvent->button() == Qt::RightButton)
	{
		QMimeData *pData = new QMimeData;
		pData->setProperty("origin", (uint) DO_Output);
		pData->setProperty("output", (qlonglong) m_pOutput);

		QDrag *pDrag = new QDrag(pEvent->widget());
		pDrag->setMimeData(pData);
		pDrag->start();
	}
}

void OutputItem::dragEnterEvent(QGraphicsSceneDragDropEvent *pEvent)
{
	const QMimeData *pData = pEvent->mimeData();

	// Check where the drag comes from
	if(pData->property("origin").isNull())
		return pEvent->ignore();

	DragOrigin origin = (DragOrigin) pData->property("origin").toUInt();
	switch(origin)
	{
	case DO_Input:
		pEvent->accept();
		break;

	case DO_Output:
	case DO_InputDeviceOutput:
	default:
		pEvent->ignore();
	};
}

void OutputItem::dragMoveEvent(QGraphicsSceneDragDropEvent *pEvent)
{
}

void OutputItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *pEvent)
{
}

void OutputItem::dropEvent(QGraphicsSceneDragDropEvent *pEvent)
{
	const QMimeData *pData = pEvent->mimeData();

	// Check where the drag comes from
	if(pData->property("origin").isNull())
		return pEvent->ignore();

	DragOrigin origin = (DragOrigin) pData->property("origin").toUInt();
	switch(origin)
	{
	case DO_Input:
		{
			// Connect to the input
			assert(!pData->property("input").isNull());
			Input *pInput = (Input *) pData->property("input").toLongLong();
			m_pOutput->connect(pInput);
			pEvent->accept();
			break;
		}

	case DO_Output:
	case DO_InputDeviceOutput:
	default:
		pEvent->ignore();
	};
}

void OutputItem::onValue(Output *pOutput, int value)
{
	float u = (value - pOutput->getMinValue()) / (float) (pOutput->getMaxValue() - pOutput->getMinValue());
	float width = u * g_width;

	m_pMeterItem->setRect(0, 0, width, g_height);
}
