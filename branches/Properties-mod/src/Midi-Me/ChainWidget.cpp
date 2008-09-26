// Includes
#include "ChainWidget.h"
#include "MainWindow.h"
#include "ChainStartItem.h"
#include "ChainEndItem.h"
#include "ProcessorItem.h"
#include "EdgeItem.h"
#include <libMidi-Me/Chain.h>
#include <libMidi-Me/DeviceManager.h>
#include <libMidi-Me/InputDevice.h>
#include <libMidi-Me/Output.h>
#include <libMidi-Me/MidiOutput.h>
#include <libMidi-Me/ProcessorFactory.h>
#include <libMidi-Me/Processor.h>
using namespace MidiMe;

#include <QtGui/QGraphicsScene>
#include <QtGui/QResizeEvent>
#include <QtGui/QMenu>
#include <QtGui/QGraphicsRectItem>
#include <QtGui/QMessageBox>


/// The hardcoded margin between items
static const float g_margin(5.0f);
/// The hardcoded maximum size of the items
static const float g_maxSize(100.0f);


/******************************
* Constructors and destructor *
******************************/

ChainWidget::ChainWidget(Chain *pChain, MainWindow *pWindow)
: QGraphicsView(pWindow), m_pWindow(pWindow), m_pChain(pChain), m_state(State_Normal)
, m_pConnectingEdge(0)
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

EdgeItem *ChainWidget::createEdge(OutputItem *pOutput, InputItem *pInput)
{
	EdgeItem *pEdge = new EdgeItem(this, pInput, pOutput);
	m_edgeItems.insert(pEdge);

	return pEdge;
}

void ChainWidget::destroyEdge(EdgeItem *pEdge)
{
	m_edgeItems.erase(pEdge);
	delete pEdge;
}

void ChainWidget::startConnecting(const QPointF &mousePos)
{
	assert(m_state == State_Normal);

	OutputItem *pOutput = 0;
	InputItem *pInput = 0;
	ChainItem *pItem = 0;

	QList<QGraphicsItem *> items = m_pScene->items(mousePos);
	for(int i = 0; i < items.size() && !(pInput || pOutput); ++i)
	{
		if(items.at(i)->type() == InputItem::Type)
			pItem = pInput = qgraphicsitem_cast<InputItem *>(items.at(i));
		else if(items.at(i)->type() == OutputItem::Type)
			pItem = pOutput = qgraphicsitem_cast<OutputItem *>(items.at(i));
	}

	if(pItem)
	{
		// First disconnect if alread connected
		if(pItem->isConnected())
			pItem->disconnect();

		// Create the temporary connection
		m_pConnectingEdge = new EdgeItem(this, pInput, pOutput);
		m_pConnectingEdge->setTempPosition(mousePos);

		// Set the connecting state
		m_state = State_Connecting;
	}
}

void ChainWidget::stopConnecting(const QPointF &mousePos)
{
	assert(m_state == State_Connecting && m_pConnectingEdge);

	OutputItem *pOutputItem = m_pConnectingEdge->getOutputItem();
	InputItem *pInputItem = m_pConnectingEdge->getInputItem();

	QList<QGraphicsItem *> items = m_pScene->items(mousePos);
	for(int i = 0; i < items.size() && !(pInputItem && pOutputItem); ++i)
	{
		if(items.at(i)->type() == OutputItem::Type && pInputItem)
		{
			pOutputItem = qgraphicsitem_cast<OutputItem *>(items.at(i));
			
			// Don't connect to the same processor
			if(pOutputItem->parentItem() && pOutputItem->parentItem() == pInputItem->parentItem())
				continue;
			
			// Connect if not yet connected
			if(!pOutputItem->isConnected())
				pOutputItem->connect(pInputItem);
		}
		else if(items.at(i)->type() == InputItem::Type && pOutputItem)
		{
			pInputItem = qgraphicsitem_cast<InputItem *>(items.at(i));

			// Don't connect to the same processor
			if(pInputItem->parentItem() && pOutputItem->parentItem() == pInputItem->parentItem())
				continue;

			// Connect if not yet connected
			if(!pInputItem->isConnected())
				m_pConnectingEdge->getOutputItem()->connect(pInputItem);
		}
	}

	// Remove the temporary connection line
	delete m_pConnectingEdge;
	m_pConnectingEdge = 0;

	// Reset the current state
	m_state = State_Normal;
}

void ChainWidget::addControlSignal()
{
	ChainEnd *pEnd = m_pChain->addChainEnd();
}


/**********************
* Protected functions *
**********************/

void ChainWidget::addChainStart(QAction *pAction)
{
	QList<QVariant> data = pAction->data().toList();

	InputDevice *pDevice = (InputDevice *) data.at(0).toLongLong();
	unsigned int outputID = data.at(1).toUInt();

	m_pChain->addChainStart(pDevice, outputID);
}

void ChainWidget::addProcessor(QAction *pAction)
{
	m_pChain->addProcessor(pAction->text().toStdString());
}

void ChainWidget::addChainEnd(QAction *pAction)
{
	QList<QVariant> data = pAction->data().toList();
	/*MidiOutput *pMidi = DeviceManager::getInstance().getMidiOutput();

	unsigned int port = data.at(0).toUInt();
	if(!pMidi->isOpened() || pMidi->getOpenedPort() != port)
	{
		if(!pMidi->open(port))
		{
			QString message = "Error opening midi port '";
			message += pMidi->getPortName(port).c_str();
			message += "': ";
			message += pMidi->getLastError().c_str();

			QMessageBox::warning(this, "Midi error", message);
			return;
		}
	}

	ControllerSignal *pCC = pMidi->createControllerSignal();
	// TEMP
	pCC->setController(16);

	ChainEnd *pEnd = m_pChain->addChainEnd(pMidi, pCC);*/
}

void ChainWidget::resizeEvent(QResizeEvent *pEvent)
{
	// Resize to size of the widget
	setSceneRect(0,0, pEvent->size().width(), pEvent->size().height());

	QGraphicsView::resizeEvent(pEvent);
	update();
}

void ChainWidget::mousePressEvent(QMouseEvent *pEvent)
{
	QGraphicsView::mousePressEvent(pEvent);
}

void ChainWidget::mouseReleaseEvent(QMouseEvent *pEvent)
{
	if(m_state == State_Normal && pEvent->button() == Qt::RightButton)
	{
		// Only show if not on item
		QPointF scenePos = mapToScene(pEvent->pos());
		QGraphicsItem *pItem = m_pScene->itemAt(scenePos);
		if(pItem)
			return QGraphicsView::mouseReleaseEvent(pEvent);

		// Generate the context menu
		QMenu *pMenu = new QMenu(this);
		generateChainStartMenu(pMenu);
		generateProcessorMenu(pMenu);
		generateChainEndMenu(pMenu);

		pMenu->popup(pEvent->globalPos());
		pEvent->accept();
	}
	else if(m_state == State_Connecting)
	{
		if(pEvent->button() == Qt::RightButton)
		{
			QPointF scenePos = mapToScene(pEvent->pos());
			stopConnecting(scenePos);
		}

		pEvent->accept();
	}
	else
		QGraphicsView::mouseReleaseEvent(pEvent);
}

void ChainWidget::mouseMoveEvent(QMouseEvent *pEvent)
{
	if(m_state == State_Normal && (pEvent->buttons() & Qt::RightButton))
	{
		QPointF scenePos = mapToScene(pEvent->pos());
		startConnecting(scenePos);
		pEvent->accept();
	}
	if(m_state == State_Connecting)
	{
		m_pConnectingEdge->setTempPosition(pEvent->posF());
		pEvent->accept();
	}
	else
		QGraphicsView::mouseMoveEvent(pEvent);
}

void ChainWidget::onStartAdded(ChainStart *pStart)
{
	assert(m_startItems.find(pStart) == m_startItems.end());

	ChainStartItem *pItem = new ChainStartItem(this, pStart);
	m_startItems[pStart] = pItem;
	
	// Position the item on the left side
	float x = -1.0f;
	float y = g_margin;
	pItem->setPos(x,y);

	// Make sure we don't collide with other items
	//! @todo Find out why there is always one item in the collidingItems list
	while(pItem->collidingItems().count() > 1)
	{
		y += 2 * g_margin;
		pItem->setPos(x,y);
	}

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
	assert(m_endItems.find(pEnd) == m_endItems.end());

	ChainEndItem *pItem = new ChainEndItem(this, pEnd);
	m_endItems[pEnd] = pItem;

	if(pItem)
		pItem->setPropertyEditor(m_pWindow->getPropertyEditor());

	// Position the item on the right side
	float x = sceneRect().right() - pItem->rect().width() + 1.0f;
	float y = g_margin;
	pItem->setPos(x,y);

	// Make sure we don't collide with other items
	//! @todo Find out why there is always one item in the collidingItems list
	while(pItem->collidingItems().count() > 1)
	{
		y += 2 * g_margin;
		pItem->setPos(x,y);
	}

	update();
}

void ChainWidget::onEndRemoving(ChainEnd *pEnd)
{
	assert(m_endItems.find(pEnd) != m_endItems.end());

	delete m_endItems[pEnd];
	m_endItems.erase(pEnd);
	update();
}

void ChainWidget::onProcessorAdded(Processor *pProcessor)
{
	assert(m_processorItems.find(pProcessor) == m_processorItems.end());

	ProcessorItem *pItem = new ProcessorItem(this, pProcessor);
	m_processorItems[pProcessor] = pItem;

	if(pItem)
		pItem->setPropertyEditor(m_pWindow->getPropertyEditor());

	update();
}

void ChainWidget::onProcessorRemoving(Processor *pProcessor)
{
	assert(m_processorItems.find(pProcessor) != m_processorItems.end());

	//! @todo Clear property editor if this was the selected processor

	delete m_processorItems[pProcessor];
	m_processorItems.erase(pProcessor);
	update();
}

void ChainWidget::destroyItems()
{
	delete m_pConnectingEdge;
	m_pConnectingEdge = 0;

	EdgeItemSet::iterator edgeIt;
	for(edgeIt = m_edgeItems.begin(); edgeIt != m_edgeItems.end(); ++edgeIt)
		delete *edgeIt;
	m_edgeItems.clear();

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

void ChainWidget::generateChainStartMenu(QMenu *pParent)
{
	QMenu *pMenu = pParent->addMenu("Add chain start");

	// Devices
	DeviceManager &devMgr = DeviceManager::getInstance();
	const InputDeviceMap &devices = devMgr.getInputDevices();
	InputDeviceMap::const_iterator devIt;

	for(devIt = devices.begin(); devIt != devices.end(); ++devIt)
	{
		InputDevice *pDevice = devIt->second;
		QMenu *pDevMenu = pMenu->addMenu(devIt->first.c_str());
		connect(pDevMenu, SIGNAL(triggered(QAction *)), SLOT(addChainStart(QAction *)));

		const OutputMap &outputs = pDevice->getAllOutputs();
		OutputMap::const_iterator it;
		
		for(it = outputs.begin(); it != outputs.end(); ++it)
		{
			unsigned int id = it->first;
			Output *pOutput = it->second;

			QString name = QString("Output %1").arg(id);
			if(pOutput->isAnalog())
				name += " (analog)";
			else
				name += " (digital)";

			QAction *pAction = pDevMenu->addAction(name);

			QList<QVariant> data;
			data.append((qlonglong) pDevice);
			data.append(id);
			pAction->setData(data);
		}

		if(outputs.empty())
			pDevMenu->setEnabled(false);
	}

	if(devices.empty())
		pMenu->setEnabled(false);
}

void ChainWidget::generateProcessorMenu(QMenu *pParent)
{
	QMenu *pMenu = pParent->addMenu("Add processor");
	connect(pMenu, SIGNAL(triggered(QAction *)), SLOT(addProcessor(QAction *)));

	ProcessorFactory &factory = ProcessorFactory::getInstance();
	const ProcessorCreatorMap &processors = factory.getAllCreators();

	ProcessorCreatorMap::const_iterator it;
	for(it = processors.begin(); it != processors.end(); ++it)
	{
		ProcessorCreator *pCreator = it->second;
		pMenu->addAction(pCreator->getType().c_str());
	}
}

void ChainWidget::generateChainEndMenu(QMenu *pParent)
{
	QMenu *pMenu = pParent->addMenu("Add chain end");

	//! @todo Support multiple
	QAction *pCCAction = pMenu->addAction("Controller Signal");
	connect(pCCAction, SIGNAL(triggered()), SLOT(addControlSignal()));

	/*DeviceManager &devMgr = DeviceManager::getInstance();
	MidiOutput *pMidi = devMgr.getMidiOutput();

	for(unsigned int i = 0; i < pMidi->numPorts(); ++i)
	{
		QMenu *pPortMenu = pMenu->addMenu(pMidi->getPortName(i).c_str());
		connect(pPortMenu, SIGNAL(triggered(QAction *)), SLOT(addChainEnd(QAction *)));

		// Available items
		QAction *pAction = pPortMenu->addAction("Controller Signal");

		QList<QVariant> data;
		data.append(i);
		pAction->setData(data);
	}

	if(pMidi->numPorts() == 0)
		pMenu->setEnabled(false);*/
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

	StartItemMap::iterator startIt;
	for(startIt = m_startItems.begin(); startIt != m_startItems.end(); ++startIt)
		startIt->second->adjustPosition();
}

void ChainWidget::distributeEndItems()
{
	if(m_endItems.empty())
		return;

	/*float size = (sceneRect().height() - g_margin) / m_endItems.size() - g_margin;
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
	}*/

	EndItemMap::iterator endIt;
	for(endIt = m_endItems.begin(); endIt != m_endItems.end(); ++endIt)
		endIt->second->adjustPosition();
}

void ChainWidget::distributeProcessorItems()
{
	if(m_processorItems.empty())
		return;

	/*float size = (sceneRect().height() - g_margin) / m_processorItems.size() - g_margin;
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
	}*/

	ProcessorItemMap::iterator processorIt;
	for(processorIt = m_processorItems.begin(); processorIt != m_processorItems.end(); ++processorIt)
		processorIt->second->adjustPosition();
}
