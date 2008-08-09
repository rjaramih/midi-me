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

	// Add value inputs
	const ValueInputSet &valueInputs = m_pProcessor->getValueInputs();
	ValueInputSet::const_iterator valueIt;
	for(valueIt = valueInputs.begin(); valueIt != valueInputs.end(); ++valueIt)
	{
		ValueInput *pInput = *valueIt;

		ValueInputItem *pItem = new ValueInputItem(pInput, this);
		pItem->setPos(x,y);
		y += pItem->rect().height() + g_margin;
	}

	// Add range inputs
	const RangeInputSet &rangeInputs = m_pProcessor->getRangeInputs();
	RangeInputSet::const_iterator rangeIt;
	for(rangeIt = rangeInputs.begin(); rangeIt != rangeInputs.end(); ++rangeIt)
	{
		RangeInput *pInput = *rangeIt;

		RangeInputItem *pItem = new RangeInputItem(pInput, this);
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

	// Add value outputs
	const ValueOutputSet &valueOutputs = m_pProcessor->getValueOutputs();
	ValueOutputSet::const_iterator valueIt;
	for(valueIt = valueOutputs.begin(); valueIt != valueOutputs.end(); ++valueIt)
	{
		ValueOutput *pOutput = *valueIt;

		ValueOutputItem *pItem = new ValueOutputItem(pOutput, this);
		pItem->setPos(x,y);
		y += pItem->rect().height() + g_margin;
	}

	// Add range outputs
	const RangeOutputSet &rangeOutputs = m_pProcessor->getRangeOutputs();
	RangeOutputSet::const_iterator rangeIt;
	for(rangeIt = rangeOutputs.begin(); rangeIt != rangeOutputs.end(); ++rangeIt)
	{
		RangeOutput *pOutput = *rangeIt;

		RangeOutputItem *pItem = new RangeOutputItem(pOutput, this);
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
