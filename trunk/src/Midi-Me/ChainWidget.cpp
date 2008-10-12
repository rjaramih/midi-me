// Includes
#include "ChainWidget.h"
#include "MainWindow.h"
#include "ChainStartItem.h"
#include "ChainEndItem.h"
#include "ProcessorItem.h"
#include "ConnectionItem.h"
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
, m_pTempConnection(0), m_pConnectingOutput(0), m_pConnectingInput(0)
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

InputItem *ChainWidget::getInputItem(Input *pInput) const
{
	InputItemMap::const_iterator it = m_inputItems.find(pInput);
	return (it == m_inputItems.end()) ? 0 : it->second;
}

OutputItem *ChainWidget::getOutputItem(Output *pOutput) const
{
	OutputItemMap::const_iterator it = m_outputItems.find(pOutput);
	return (it == m_outputItems.end()) ? 0 : it->second;
}

ConnectionItem *ChainWidget::getConnectionItem(Connection *pConnection) const
{
	ConnectionItemMap::const_iterator it = m_connectionItems.find(pConnection);
	return (it == m_connectionItems.end()) ? 0 : it->second;
}

void ChainWidget::update()
{
	distributeStartItems();
	distributeEndItems();
	distributeProcessorItems();
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
			m_pChain->removeConnection(pItem->getConnectionItem()->getConnection());

		// Create the temporary connection
		m_pTempConnection = new ConnectionItem(this, 0);
		m_pConnectingOutput = pOutput;
		m_pConnectingInput = pInput;

		if(pOutput)
			m_pTempConnection->setTempStartPosition(mousePos);
		else
			m_pTempConnection->setTempEndPosition(mousePos);

		// Set the connecting state
		m_state = State_Connecting;
	}
}

void ChainWidget::stopConnecting(const QPointF &mousePos)
{
	assert(m_state == State_Connecting && m_pTempConnection);

	OutputItem *pOutputItem = m_pConnectingOutput;
	InputItem *pInputItem = m_pConnectingInput;

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
				m_pChain->addConnection(pInputItem->getInput(), pOutputItem->getOutput());
		}
		else if(items.at(i)->type() == InputItem::Type && pOutputItem)
		{
			pInputItem = qgraphicsitem_cast<InputItem *>(items.at(i));

			// Don't connect to the same processor
			if(pInputItem->parentItem() && pOutputItem->parentItem() == pInputItem->parentItem())
				continue;

			// Connect if not yet connected
			if(!pInputItem->isConnected())
				m_pChain->addConnection(pInputItem->getInput(), pOutputItem->getOutput());
		}
	}

	// Remove the temporary connection line
	delete m_pTempConnection;
	m_pTempConnection = 0;

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

void ChainWidget::resizeEvent(QResizeEvent *pEvent)
{
	// Resize to size of the widget
	setSceneRect(0,0, pEvent->size().width(), pEvent->size().height());

	QGraphicsView::resizeEvent(pEvent);
	update();
}

void ChainWidget::mousePressEvent(QMouseEvent *pEvent)
{
	// Clear the properties if not clicked on item
	QPointF scenePos = mapToScene(pEvent->pos());
	QGraphicsItem *pItem = m_pScene->itemAt(scenePos);
	if(!pItem)
		m_pWindow->getPropertyEditor()->clear();

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
		if(m_pConnectingInput)
			m_pTempConnection->setTempStartPosition(pEvent->posF());
		else
			m_pTempConnection->setTempEndPosition(pEvent->posF());

		pEvent->accept();
	}
	else
		QGraphicsView::mouseMoveEvent(pEvent);
}

void ChainWidget::onStartAdded(ChainStart *pStart)
{
	assert(m_startItems.find(pStart) == m_startItems.end());

	// Create the associated item
	ChainStartItem *pItem = new ChainStartItem(this, pStart);
	m_startItems[pStart] = pItem;
	
	// Position the item on the left side
	float x = -1.0f;
	float y = g_margin;
	pItem->setPos(x,y);

	float maxY = rect().height() - ChainItem::height - ChainItem::margin;

	// Make sure we don't collide with other items
	QList<QGraphicsItem *> colItems = getColliders(pItem);
	while(!colItems.empty() && y <= maxY)
	{
		y += 2 * g_margin;
		pItem->setPos(x,y);

		colItems = getColliders(pItem);
	}

	// Store the output item
	m_outputItems[pStart->getOutput()] = pItem;

	update();
}

void ChainWidget::onStartRemoving(ChainStart *pStart)
{
	assert(m_startItems.find(pStart) != m_startItems.end());

	// Remove the output item
	m_outputItems.erase(m_startItems[pStart]->getOutput());

	// Destroy the associated item
	delete m_startItems[pStart];
	m_startItems.erase(pStart);

	update();
}

void ChainWidget::onEndAdded(ChainEnd *pEnd)
{
	assert(m_endItems.find(pEnd) == m_endItems.end());

	// Create the associated item
	ChainEndItem *pItem = new ChainEndItem(this, pEnd);
	m_endItems[pEnd] = pItem;

	if(pItem)
		pItem->setPropertyEditor(m_pWindow->getPropertyEditor());

	// Position the item on the right side
	float x = sceneRect().right() - pItem->rect().width() + 1.0f;
	float y = g_margin;
	pItem->setPos(x,y);

	float maxY = rect().height() - ChainItem::height - ChainItem::margin;

	// Make sure we don't collide with other items
	QList<QGraphicsItem *> colItems = getColliders(pItem);
	while(!colItems.empty() && y <= maxY)
	{
		y += 2 * g_margin;
		pItem->setPos(x,y);

		colItems = getColliders(pItem);
	}

	// Store the input item
	m_inputItems[pEnd->getInput()] = pItem;

	update();
}

void ChainWidget::onEndRemoving(ChainEnd *pEnd)
{
	assert(m_endItems.find(pEnd) != m_endItems.end());

	// Remove the input item
	m_inputItems.erase(m_endItems[pEnd]->getInput());

	// Destroy the associated item
	delete m_endItems[pEnd];
	m_endItems.erase(pEnd);

	update();
}

void ChainWidget::onProcessorAdded(Processor *pProcessor)
{
	assert(m_processorItems.find(pProcessor) == m_processorItems.end());

	// Create the associated item
	ProcessorItem *pItem = new ProcessorItem(this, pProcessor);
	m_processorItems[pProcessor] = pItem;

	pItem->setPropertyEditor(m_pWindow->getPropertyEditor());

	// Position the item in the center
	float x = 0.5f * rect().width() - pItem->rect().width();
	float y = g_margin;
	pItem->setPos(x,y);

	float maxY = rect().height() - pItem->rect().height() - g_margin;

	// Make sure we don't collide with other items
	QList<QGraphicsItem *> colItems = getColliders(pItem);
	while(!colItems.empty() && y <= maxY)
	{
		y += 2 * g_margin;
		pItem->setPos(x,y);

		colItems = getColliders(pItem);
	}

	// Add the input items
	const InputItemMap &inputs = pItem->getAllInputs();
	for(InputItemMap::const_iterator it = inputs.begin(); it != inputs.end(); ++it)
		m_inputItems[it->first] = it->second;

	// Add the output items
	const OutputItemMap &outputs = pItem->getAllOutputs();
	for(OutputItemMap::const_iterator it = outputs.begin(); it != outputs.end(); ++it)
		m_outputItems[it->first] = it->second;

	update();
}

void ChainWidget::onProcessorRemoving(Processor *pProcessor)
{
	assert(m_processorItems.find(pProcessor) != m_processorItems.end());
	ProcessorItem *pItem = m_processorItems[pProcessor];

	//! @todo Clear property editor if this was the selected processor

	// Remove the input items
	const InputItemMap &inputs = pItem->getAllInputs();
	for(InputItemMap::const_iterator it = inputs.begin(); it != inputs.end(); ++it)
		m_inputItems.erase(it->first);

	// Remove the output items
	const OutputItemMap &outputs = pItem->getAllOutputs();
	for(OutputItemMap::const_iterator it = outputs.begin(); it != outputs.end(); ++it)
		m_outputItems.erase(it->first);

	// Destroy the associated item
	delete m_processorItems[pProcessor];
	m_processorItems.erase(pProcessor);

	update();
}

void ChainWidget::onConnectionAdded(Connection *pConnection)
{
	assert(m_connectionItems.find(pConnection) == m_connectionItems.end());

	ConnectionItem *pItem = new ConnectionItem(this, pConnection);
	m_connectionItems[pConnection] = pItem;

	update();
}

void ChainWidget::onConnectionRemoving(Connection *pConnection)
{
	assert(m_connectionItems.find(pConnection) != m_connectionItems.end());

	delete m_connectionItems[pConnection];
	m_connectionItems.erase(pConnection);
	
	update();
}

void ChainWidget::destroyItems()
{
	delete m_pTempConnection;
	m_pTempConnection = 0;

	ConnectionItemMap::iterator connIt;
	for(connIt = m_connectionItems.begin(); connIt != m_connectionItems.end(); ++connIt)
		delete connIt->second;
	m_connectionItems.clear();

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

	//! @todo Use a factory for the chain end items

	QAction *pCCAction = pMenu->addAction("Controller Signal");
	connect(pCCAction, SIGNAL(triggered()), SLOT(addControlSignal()));
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

/** Returns the list of non-children items that collide with pItem. */
QList<QGraphicsItem *> ChainWidget::getColliders(const QGraphicsItem *pItem)
{
	QList<QGraphicsItem *> result;
	QList<QGraphicsItem *> items = pItem->collidingItems();
	
	//! @todo Why is there always one colliding item?
	for(int i = 0; i < items.size(); ++i)
	{
		if(!pItem->isAncestorOf(items.at(i)) && !items.at(i)->isAncestorOf(pItem))
			result.push_back(items.at(i));
	}

	return result;
}
