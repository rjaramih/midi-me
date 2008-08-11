// Includes
#include "ProcessorItem.h"
#include "InputItem.h"
#include "OutputItem.h"
#include <libMidi-Me/Processor.h>
using namespace MidiMe;


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

ProcessorItem::ProcessorItem(Processor *pProcessor, QGraphicsItem *pParent)
: QGraphicsRectItem(pParent), m_pProcessor(pProcessor)
{
	assert(m_pProcessor);

	// Setup item
	setFlag(ItemIsSelectable);
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


/**********************
* Protected functions *
**********************/

void ProcessorItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *pEvent)
{
	return QGraphicsRectItem::contextMenuEvent(pEvent);
}

QVariant ProcessorItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
	return QGraphicsRectItem::itemChange(change, value);
}

void ProcessorItem::createInputs()
{
	float x = 0.0f;
	float y = g_margin;

	// Add inputs
	const InputSet &inputs = m_pProcessor->getInputs();
	InputSet::const_iterator it;
	for(it = inputs.begin(); it != inputs.end(); ++it)
	{
		Input *pInput = *it;

		InputItem *pItem = new InputItem(pInput, this);
		pItem->setPos(x,y);
		y += pItem->rect().height() + g_margin;
	}

	// Expand if necessary
	if(y > rect().height())
		setRect(0,0, g_width, y);
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
	float x = g_width;
	float y = g_margin;

	// Add outputs
	const OutputSet &outputs = m_pProcessor->getOutputs();
	OutputSet::const_iterator it;
	for(it = outputs.begin(); it != outputs.end(); ++it)
	{
		Output *pOutput = *it;

		OutputItem *pItem = new OutputItem(pOutput, this);
		pItem->setPos(x,y);
		y += pItem->rect().height() + g_margin;
	}

	// Expand if necessary
	if(y > rect().height())
		setRect(0,0, g_width, y);
}

void ProcessorItem::destroyOutputs()
{
	OutputItemMap::iterator it;
	for(it = m_outputItems.begin(); it != m_outputItems.end(); ++it)
		delete it->second;
	m_outputItems.clear();
}
