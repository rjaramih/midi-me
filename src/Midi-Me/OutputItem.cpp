// Includes
#include "OutputItem.h"
#include "InputItem.h"
#include "ChainWidget.h"
#include "ConnectionItem.h"
using namespace MidiMe;

#include <QtCore/QUrl>


/******************************
* Constructors and destructor *
******************************/

OutputItem::OutputItem(ChainWidget *pChainWidget, Output *pOutput, QGraphicsItem *pParent)
: ChainItem(pChainWidget, pParent), m_pOutput(pOutput)
{
	assert(m_pOutput);
	m_pOutput->addListener(this);

	// The anchor to attach an edge to
	m_localAnchor.setX(width - margin);
	m_localAnchor.setY(height * 0.5f);

	// Info text
	QGraphicsTextItem *pInfo = new QGraphicsTextItem(this);
	/*QString html = QString("<center>") + m_pOutput->getInfo().c_str() + "</center>";
	pInfo->setHtml(html);*/
	pInfo->setPlainText(m_pOutput->getInfo().c_str());
	pInfo->setPos(2 * ChainItem::margin, 0);
	pInfo->setTextWidth(rect().width() - 2 * ChainItem::margin);
}

OutputItem::~OutputItem()
{
	m_pOutput->removeListener(this);
}


/******************
* Other functions *
******************/

bool OutputItem::isConnected() const
{
	return m_pOutput->isConnected();
}

ConnectionItem *OutputItem::getConnectionItem() const
{
	if(!m_pOutput->isConnected())
		return 0;

	return m_pChainWidget->getConnectionItem(m_pOutput->getConnection());
}

void OutputItem::onValue(Output *pOutput, real value)
{
	if(!m_pChainWidget->isEnabled())
		return;

	//float u = (value - pOutput->getMinValue()) / (float) (pOutput->getMaxValue() - pOutput->getMinValue());
	real u = value;
	float meterWidth = u * width;

	m_pMeterItem->setRect(0, 0, meterWidth, height);
}

QVariant OutputItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if(change == ItemPositionHasChanged && m_pOutput->isConnected())
		m_pChainWidget->getConnectionItem(m_pOutput->getConnection())->adjust();

	return ChainItem::itemChange(change, value);
}
