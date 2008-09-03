// Includes
#include "ProcessorItem.h"
#include "InputItem.h"
#include "OutputItem.h"
#include "ChainWidget.h"
#include "EdgeItem.h"
#include <libMidi-Me/Processor.h>
using namespace MidiMe;

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>


/// The hardcoded margin between items
static const float g_margin(5.0f);
// The hardcoded width of a processor item
static const float g_width(100.0f);
/// The hardcoded minimum height of a processor item
static const float g_minHeight(25.0f);
/// The hardcoded maximum height of a processor item
static const float g_maxHeight(100.0f);


/******************************
* Constructors and destructor *
******************************/

ProcessorItem::ProcessorItem(ChainWidget *pChainWidget, Processor *pProcessor, QGraphicsItem *pParent)
: QGraphicsRectItem(pParent), m_pChainWidget(pChainWidget), m_pProcessor(pProcessor)
{
	assert(m_pChainWidget && m_pProcessor);

	// Make this a top-level item if no parent is provided
	if(!pParent)
		m_pChainWidget->getScene()->addItem(this);

	// Setup item
	//setFlag(ItemIsSelectable);
	setFlag(ItemIsMovable);
	//setFlag(ItemIsFocusable);

	createInputs();
	createOutputs();
}

ProcessorItem::~ProcessorItem()
{
	destroyInputs();
	destroyOutputs();
}


/******************
* Other functions *
******************/

/** Adjust the current position so it fits the viewport */
void ProcessorItem::adjustPosition()
{
	QPointF position = pos();
	adjustPosition(position);
	setPos(position);
}



/**********************
* Protected functions *
**********************/

void ProcessorItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *pEvent)
{
	return QGraphicsRectItem::contextMenuEvent(pEvent);
}

QVariant ProcessorItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if(change == ItemPositionChange)
	{
		QPointF position = value.toPointF();
		adjustPosition(position);
		return position;
	}

	// Propagate to children (this event is only sent when the local position is changed)
	else if(change == ItemPositionHasChanged)
	{
		// Adjust all input edges
		for(InputItemMap::iterator it = m_inputItems.begin(); it != m_inputItems.end(); ++it)
			if(it->second->isConnected())
				it->second->getConnectedEdge()->adjust();

		// Adjust all output edges
		for(OutputItemMap::iterator it = m_outputItems.begin(); it != m_outputItems.end(); ++it)
			if(it->second->isConnected())
				it->second->getConnectedEdge()->adjust();
	}

	return QGraphicsRectItem::itemChange(change, value);
}

void ProcessorItem::createInputs()
{
	float x = -InputItem::width + g_margin;
	float y = g_margin;

	// Add inputs
	const InputSet &inputs = m_pProcessor->getInputs();
	InputSet::const_iterator it;
	for(it = inputs.begin(); it != inputs.end(); ++it)
	{
		Input *pInput = *it;

		InputItem *pItem = new InputItem(m_pChainWidget, pInput, this);
		pItem->setPos(x,y);
		m_inputItems[pInput] = pItem;

		y += pItem->rect().height() + g_margin;
	}

	// Expand if necessary
	float totalHeight = y + g_margin;
	if(totalHeight > rect().height())
		setRect(0,0, g_width, totalHeight);
}

void ProcessorItem::destroyInputs()
{
	InputItemMap::iterator it;
	for(it = m_inputItems.begin(); it != m_inputItems.end(); ++it)
		delete it->second;
	m_inputItems.clear();
}

void ProcessorItem::createOutputs()
{
	float x = g_width - g_margin;
	float y = g_margin;

	// Add outputs
	const OutputSet &outputs = m_pProcessor->getOutputs();
	OutputSet::const_iterator it;
	for(it = outputs.begin(); it != outputs.end(); ++it)
	{
		Output *pOutput = *it;

		OutputItem *pItem = new OutputItem(m_pChainWidget, pOutput, this);
		pItem->setPos(x,y);
		m_outputItems[pOutput] = pItem;

		y += pItem->rect().height() + g_margin;
	}

	// Expand if necessary
	float height = y + g_margin;
	if(height > rect().height())
		setRect(0,0, g_width, height);
}

void ProcessorItem::destroyOutputs()
{
	OutputItemMap::iterator it;
	for(it = m_outputItems.begin(); it != m_outputItems.end(); ++it)
		delete it->second;
	m_outputItems.clear();
}

void ProcessorItem::adjustPosition(QPointF &position)
{
	QGraphicsScene *pScene = getScene();
	assert(pScene && pScene->views().size() == 1);
	QGraphicsView *pView = pScene->views().first();

	// Make sure the item stays in the visible scene
	float minX = InputItem::width + g_margin + InputItem::width;
	float maxX = pView->sceneRect().width() - boundingRect().width() - 2 * OutputItem::width - g_margin;
	if(position.x() < minX)
		position.setX(minX);
	if(position.x() > maxX)
		position.setX(maxX);

	float maxY = pView->sceneRect().bottom() - boundingRect().height() - g_margin;
	float posY = position.y();
	if(position.y() < g_margin)
		position.setY(g_margin);
	if(position.y() > maxY)
		position.setY(maxY);
}

QGraphicsScene *ProcessorItem::getScene() const
{
	const QGraphicsItem *pItem = this;
	QGraphicsScene *pScene = scene();

	while(!pScene)
	{
		pItem = pItem->parentItem();
		pScene = pItem->scene();
	}

	return pScene;
}
