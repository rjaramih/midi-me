// Includes
#include "OutputItem.h"
#include "InputItem.h"
#include "ChainWidget.h"
#include "EdgeItem.h"
using namespace MidiMe;


/************
* OutputItem *
************/

OutputItem::OutputItem(ChainWidget *pChainWidget, Output *pOutput, QGraphicsItem *pParent)
: ChainItem(pChainWidget, pParent), m_pOutput(pOutput)
{
	assert(m_pOutput);
	m_pOutput->addListener(this);

	// The anchor to attach an edge to
	m_localAnchor.setX(width - margin);
	m_localAnchor.setY(height * 0.5f);
}

OutputItem::~OutputItem()
{
	m_pOutput->removeListener(this);
}

void OutputItem::connect(InputItem *pInputItem)
{
	if(pInputItem)
	{
		// Connect
		m_pOutput->connect(pInputItem->getInput());

		// Add edge
		m_pConnectedEdge = m_pChainWidget->createEdge(this, pInputItem);
		pInputItem->setConnectedEdge(m_pConnectedEdge);
	}
	else
		disconnect();
}

void OutputItem::disconnect()
{
	if(!m_pConnectedEdge)
		return;

	// Disconnect
	m_pOutput->disconnect();

	// Destroy edge
	InputItem *pInputItem = m_pConnectedEdge->getInputItem();
	pInputItem->setConnectedEdge(0);

	m_pChainWidget->destroyEdge(m_pConnectedEdge);
	m_pConnectedEdge = 0;
}

void OutputItem::onValue(Output *pOutput, real value)
{
	//float u = (value - pOutput->getMinValue()) / (float) (pOutput->getMaxValue() - pOutput->getMinValue());
	real u = value;
	float meterWidth = u * width;

	m_pMeterItem->setRect(0, 0, meterWidth, height);
}
