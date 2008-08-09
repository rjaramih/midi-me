// Includes
#include "ChainWidget.h"
#include "ChainStartItem.h"
//#include "ChainEndItem.h"
#include "ProcessorItem.h"
#include <libMidi-Me/Chain.h>
using namespace MidiMe;

#include <QtGui/QGraphicsScene>
#include <QtGui/QResizeEvent>
#include <QtGui/QMenu>
#include <QtGui/QGraphicsRectItem>


/// The hardcoded margin between items
static const float g_margin(5.0f);
/// The hardcoded maximum size of the items
static const float g_maxSize(100.0f);


/******************************
* Constructors and destructor *
******************************/

ChainWidget::ChainWidget(Chain *pChain, QWidget *pParent)
: QGraphicsView(pParent), m_pChain(pChain)
{
	assert(m_pChain);

	// Settings
	setInteractive(true);

	m_pScene = new QGraphicsScene(this);
	setScene(m_pScene);

	update();

	m_pChain->addListener(this);
}

ChainWidget::~ChainWidget()
{
	m_pChain->removeListener(this);
	destroyItems();
	delete m_pScene;
}


/******************
* Other functions *
******************/

void ChainWidget::update()
{
	distributeStartItems();
	distributeEndItems();
	distributeProcessorItems();
}

void ChainWidget::addChainStart()
{
	m_pChain->addChainStart();
}

void ChainWidget::addChainEnd()
{
	m_pChain->addChainEnd();
}

void ChainWidget::addProcessor(const QString &type)
{
	m_pChain->addProcessor(type.toStdString());
}


/**********************
* Protected functions *
**********************/

void ChainWidget::resizeEvent(QResizeEvent *pEvent)
{
	// Resize to size of the widget
	setSceneRect(0,0, pEvent->size().width(), pEvent->size().height());

	QGraphicsView::resizeEvent(pEvent);
	update();
}

void ChainWidget::contextMenuEvent(QContextMenuEvent *pEvent)
{
	// Only show chain context menu if not on item
	QPointF scenePos = mapToScene(pEvent->pos());
	QGraphicsItem *pItem = m_pScene->itemAt(scenePos);
	if(pItem)
		return QGraphicsView::contextMenuEvent(pEvent);


	// Generate the context menu
	QMenu *pMenu = new QMenu(this);
	pMenu->addAction("Add chain start", this, SLOT(addChainStart()));
	//! @todo Add processor
	pMenu->addAction("Add chain end", this, SLOT(addChainEnd()));

	pMenu->popup(pEvent->globalPos());
	pEvent->accept();
}

void ChainWidget::onStartAdded(ChainStart *pStart)
{
	assert(m_startItems.find(pStart) == m_startItems.end());

	ChainStartItem *pItem = new ChainStartItem(pStart);
	m_startItems[pStart] = pItem;
	m_pScene->addItem(pItem);

	update();
}

void ChainWidget::onStartRemoving(ChainStart *pStart)
{
	assert(m_startItems.find(pStart) != m_startItems.end());

	delete m_startItems[pStart];
	m_startItems.erase(pStart);
	update();
}

void ChainWidget::onEndAdded(ChainEnd *pEnd)
{
	/*assert(m_endItems.find(pEnd) == m_endItems.end());

	ChainStartItem *pItem = new ChainStartItem(pStart);
	m_startItems[pStart] = pItem;
	m_pScene->addItem(pItem);

	update();*/
}

void ChainWidget::onEndRemoving(ChainEnd *pEnd)
{
	/*assert(m_endItems.find(pEnd) != m_endItems.end());

	delete m_endItems[pEnd];
	m_endItems.erase(pEnd);
	update();*/
}

void ChainWidget::onProcessorAdded(Processor *pProcessor)
{
	assert(m_processorItems.find(pProcessor) == m_processorItems.end());

	ProcessorItem *pItem = new ProcessorItem(pProcessor);
	m_processorItems[pProcessor] = pItem;
	m_pScene->addItem(pItem);

	update();
}

void ChainWidget::onProcessorRemoving(Processor *pProcessor)
{
	assert(m_processorItems.find(pProcessor) != m_processorItems.end());

	delete m_processorItems[pProcessor];
	m_processorItems.erase(pProcessor);
	update();
}

void ChainWidget::addProcessor(QAction *pAction)
{
	addProcessor(pAction->text());
}

void ChainWidget::destroyItems()
{
	StartItemMap::iterator startIt;
	for(startIt = m_startItems.begin(); startIt != m_startItems.end(); ++startIt)
		delete startIt->second;
	m_startItems.clear();

	EndItemMap::iterator endIt;
	for(endIt = m_endItems.begin(); endIt != m_endItems.end(); ++endIt)
		delete endIt->second;
	m_endItems.clear();

	ProcessorItemMap::iterator processorIt;
	for(processorIt = m_processorItems.begin(); processorIt != m_processorItems.end(); ++processorIt)
		delete processorIt->second;
	m_processorItems.clear();
}

void ChainWidget::distributeStartItems()
{
	if(m_startItems.empty())
		return;

	/*float size = (sceneRect().height() - g_margin) / m_startItems.size() - g_margin;
	if(size > g_maxSize)
		size = g_maxSize;

	float x = 0;
	float y = g_margin;

	StartItemMap::iterator startIt;
	for(startIt = m_startItems.begin(); startIt != m_startItems.end(); ++startIt)
	{
		startIt->second->setRect(0,0, size,size);
		startIt->second->setPos(x,y);
		y += size + g_margin;
	}*/
}

void ChainWidget::distributeEndItems()
{
	if(m_endItems.empty())
		return;

	float size = (sceneRect().height() - g_margin) / m_endItems.size() - g_margin;
	if(size > g_maxSize)
		size = g_maxSize;

	float x = sceneRect().right() - size;
	float y = g_margin;

	EndItemMap::iterator endIt;
	for(endIt = m_endItems.begin(); endIt != m_endItems.end(); ++endIt)
	{
		endIt->second->setRect(0,0, size,size);
		endIt->second->setPos(x,y);
		y += size + g_margin;
	}
}

void ChainWidget::distributeProcessorItems()
{
	if(m_processorItems.empty())
		return;

	float size = (sceneRect().height() - g_margin) / m_processorItems.size() - g_margin;
	if(size > g_maxSize)
		size = g_maxSize;

	float x = sceneRect().width() * 0.5f;
	float y = g_margin;

	ProcessorItemMap::iterator processorIt;
	for(processorIt = m_processorItems.begin(); processorIt != m_processorItems.end(); ++processorIt)
	{
		processorIt->second->setRect(0,0, size,size);
		processorIt->second->setPos(x,y);
		y += size + g_margin;
	}
}
