// Includes
#include "InputItem.h"
#include "DragData.h"
#include <libMidi-Me/Output.h>
using namespace MidiMe;

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsSceneMouseEvent>
#include <QtCore/QMimeData>
#include <QtGui/QDrag>


/// The hardcoded margin between items
static const float g_margin(5.0f);
static const float g_width(50.0f);
static const float g_height(15.0f);


/************
* InputItem *
************/

InputItem::InputItem(Input *pInput, QGraphicsItem *pParent)
: QGraphicsRectItem(pParent), m_pInput(pInput), m_pMeterItem(0)
{
	assert(m_pInput);

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

	m_pInput->addListener(this);

	// Enable drag-and-drop
	setAcceptDrops(true);
}

InputItem::~InputItem()
{
	delete m_pMeterItem;

	m_pInput->removeListener(this);
}

void InputItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *pEvent)
{
	return QGraphicsRectItem::contextMenuEvent(pEvent);
}

QVariant InputItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
	return QGraphicsRectItem::itemChange(change, value);
}

void InputItem::mousePressEvent(QGraphicsSceneMouseEvent *pEvent)
{
	// Start drag-and-drop on right mouse click
	if(pEvent->button() == Qt::RightButton)
	{
		QMimeData *pData = new QMimeData;
		pData->setProperty("origin", (uint) DO_Input);
		pData->setProperty("input", (qlonglong) m_pInput);

		QDrag *pDrag = new QDrag(pEvent->widget());
		pDrag->setMimeData(pData);
		pDrag->start();
	}
}

void InputItem::dragEnterEvent(QGraphicsSceneDragDropEvent *pEvent)
{
	const QMimeData *pData = pEvent->mimeData();

	// Check where the drag comes from
	if(pData->property("origin").isNull())
		return pEvent->ignore();

	DragOrigin origin = (DragOrigin) pData->property("origin").toUInt();
	switch(origin)
	{
	case DO_Output:
		pEvent->accept();
		break;

	case DO_Input:
	case DO_InputDeviceOutput:
	default:
		pEvent->ignore();
	};
}

void InputItem::dragMoveEvent(QGraphicsSceneDragDropEvent *pEvent)
{
}

void InputItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *pEvent)
{
}

void InputItem::dropEvent(QGraphicsSceneDragDropEvent *pEvent)
{
	const QMimeData *pData = pEvent->mimeData();

	// Check where the drag comes from
	if(pData->property("origin").isNull())
		return pEvent->ignore();

	DragOrigin origin = (DragOrigin) pData->property("origin").toUInt();
	switch(origin)
	{
	case DO_Output:
		{
			// Connect to the input
			assert(!pData->property("output").isNull());
			Output *pOutput = (Output *) pData->property("output").toLongLong();
			pOutput->connect(m_pInput);
			pEvent->accept();
			break;
		}

	case DO_Input:
	case DO_InputDeviceOutput:
	default:
		pEvent->ignore();
	};
}

void InputItem::onValue(Input *pInput, int value)
{
	float u = (value - pInput->getMinValue()) / (float) (pInput->getMaxValue() - pInput->getMinValue());
	float width = u * g_width;

	m_pMeterItem->setRect(0, 0, width, g_height);
}
