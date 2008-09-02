// Includes
#include "InputItem.h"
#include "OutputItem.h"
#include "EdgeItem.h"
using namespace MidiMe;


/************
* InputItem *
************/

InputItem::InputItem(ChainWidget *pChainWidget, Input *pInput, QGraphicsItem *pParent)
: ChainItem(pChainWidget, pParent), m_pInput(pInput)
{
	assert(m_pInput);
	m_pInput->addListener(this);

	// The anchor to attach an edge to
	m_localAnchor.setX(margin);
	m_localAnchor.setY(height * 0.5f);
}

InputItem::~InputItem()
{
	m_pInput->removeListener(this);
}

/******************
* Other functions *
******************/

void InputItem::disconnect()
{
	if(!m_pConnectedEdge)
		return;

	// The output is in charge of connections
	m_pConnectedEdge->getOutputItem()->disconnect();
}

void InputItem::onValue(Input *pInput, int value)
{
	float u = (value - pInput->getMinValue()) / (float) (pInput->getMaxValue() - pInput->getMinValue());
	float meterWidth = u * width;

	m_pMeterItem->setRect(0, 0, meterWidth, height);
}
