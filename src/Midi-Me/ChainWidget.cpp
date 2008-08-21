// Includes
#include "ChainWidget.h"
#include "ChainStartItem.h"
#include "ChainEndItem.h"
#include "ProcessorItem.h"
#include <libMidi-Me/Chain.h>
#include <libMidi-Me/DeviceManager.h>
#include <libMidi-Me/InputDevice.h>
#include <libMidi-Me/Output.h>
#include <libMidi-Me/MidiOutput.h>
#include <libMidi-Me/ControllerSignal.h>
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
}

void ChainWidget::addChainEnd(QAction *pAction)
{
	QList<QVariant> data = pAction->data().toList();
	MidiOutput *pMidi = DeviceManager::getInstance().getMidiOutput();

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

	ChainEnd *pEnd = m_pChain->addChainEnd();
	ControllerSignal *pCC = pMidi->createControllerSignal();

	// TEMP
	pCC->setController(16);

	pEnd->setMidi(pMidi);
	pEnd->setInput(pCC);
}

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
	generateChainStartMenu(pMenu);
	generateProcessorMenu(pMenu);
	generateChainEndMenu(pMenu);

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
	assert(m_endItems.find(pEnd) == m_endItems.end());

	ChainEndItem *pItem = new ChainEndItem(pEnd);
	m_endItems[pEnd] = pItem;
	m_pScene->addItem(pItem);

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

	// TEMP
	pMenu->setEnabled(false);
}

void ChainWidget::generateChainEndMenu(QMenu *pParent)
{
	QMenu *pMenu = pParent->addMenu("Add chain end");

	DeviceManager &devMgr = DeviceManager::getInstance();
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
		pMenu->setEnabled(false);
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
}
