// Includes
#include "ChainStartItem.h"
#include "OutputItem.h"
#include <libMidi-Me/ChainStart.h>
#include <libMidi-Me/Output.h>
#include <libMidi-Me/DeviceManager.h>
#include <libMidi-Me/InputDevice.h>
using namespace MidiMe;

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>
#include <QtGui/QMenu>
#include <QtGui/QGraphicsSceneContextMenuEvent>


/// The hardcoded margin between items
static const float g_margin(5.0f);
static const float g_stdWidth(50.0f);
static const float g_stdHeight(15.0f);


/******************************
* Constructors and destructor *
******************************/

ChainStartItem::ChainStartItem(ChainStart *pChainStart, QGraphicsItem *pParent)
: QGraphicsRectItem(pParent), m_pChainStart(pChainStart), m_pOutputItem(0)
{
	assert(m_pChainStart);

	// Setup item
	setFlag(ItemIsSelectable);
	setFlag(ItemIsMovable);
	setFlag(ItemIsFocusable);

	createOutputItem();
	m_pChainStart->addListener(this);
}

ChainStartItem::~ChainStartItem()
{
	m_pChainStart->removeListener(this);
	delete m_pOutputItem;
}


/******************
* Other functions *
******************/


/**********************
* Protected functions *
**********************/

void ChainStartItem::selectDevice(QAction *pAction)
{
	string name = pAction->text().toStdString();
	m_pChainStart->setDevice(DeviceManager::getInstance().getInputDevice(name));
}

void ChainStartItem::selectValueOutput(QAction *pAction)
{
	size_t i = pAction->data().toInt();
	m_pChainStart->setOutput(m_pChainStart->getDevice()->getValueOutput(i));
}

void ChainStartItem::selectRangeOutput(QAction *pAction)
{
	size_t i = pAction->data().toInt();
	m_pChainStart->setOutput(m_pChainStart->getDevice()->getRangeOutput(i));
}

void ChainStartItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *pEvent)
{
	DeviceManager &devMgr = DeviceManager::getInstance();
	InputDevice *pDevice = m_pChainStart->getDevice();

	// Generate the context menu
	QMenu *pMenu = new QMenu(scene()->views().first());

	
	// Input devices
	QMenu *pDeviceMenu = pMenu->addMenu("Input device");
	connect(pDeviceMenu, SIGNAL(triggered(QAction *)), SLOT(selectDevice(QAction *)));

	const InputDeviceMap &devices = devMgr.getInputDevices();
	InputDeviceMap::const_iterator devIt;
	for(devIt = devices.begin(); devIt != devices.end(); ++devIt)
	{
		QAction *pAction = pDeviceMenu->addAction(devIt->first.c_str());
		pAction->setCheckable(true);

		if(pDevice == devIt->second)
			pAction->setChecked(true);
	}

	if(devices.empty())
		pDeviceMenu->setEnabled(false);
	
	// Outputs for the selected input device
	QMenu *pOutputMenu = pMenu->addMenu("Signal");

	if(pDevice)
	{
		// Value outputs
		QMenu *pValueOutputMenu = pOutputMenu->addMenu("Value output");
		connect(pValueOutputMenu, SIGNAL(triggered(QAction *)), SLOT(selectValueOutput(QAction *)));

		size_t num = pDevice->numValueOutputs();
		for(size_t i = 0; i < num; ++i)
		{
			QAction *pAction = pValueOutputMenu->addAction(QString("Value output %1").arg(i + 1));
			pAction->setData(i);
			pAction->setCheckable(true);

			if(m_pChainStart->getOutput() == pDevice->getValueOutput(i))
				pAction->setChecked(true);
		}

		if(num == 0)
			pValueOutputMenu->setEnabled(false);

		// Range outputs
		QMenu *pRangeOutputMenu = pOutputMenu->addMenu("Range output");
		connect(pRangeOutputMenu, SIGNAL(triggered(QAction *)), SLOT(selectRangeOutput(QAction *)));

		num = pDevice->numRangeOutputs();
		for(size_t i = 0; i < num; ++i)
		{
			QAction *pAction = pRangeOutputMenu->addAction(QString("Range output %1").arg(i + 1));
			pAction->setData(i);
			pAction->setCheckable(true);

			if(m_pChainStart->getOutput() == pDevice->getRangeOutput(i))
				pAction->setChecked(true);
		}

		if(num == 0)
			pRangeOutputMenu->setEnabled(false);
	}
	else
		pOutputMenu->setEnabled(false);

	
	pMenu->popup(pEvent->screenPos());
	pEvent->accept();
}

QVariant ChainStartItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if(change == ItemPositionChange)
	{
		assert(scene() && scene()->views().size() == 1);
		QGraphicsView *pView = scene()->views().first();

		QPointF pos = value.toPointF();

		// Make sure the item stays at the left edge
		pos.setX(-1.0f);

		// Make sure the item stays in the visible scene
		float maxY = pView->sceneRect().bottom() - rect().height() - g_margin;
		float posY = pos.y();
		if(pos.y() < 0.0f)
			pos.setY(0.0f);
		if(pos.y() > maxY)
			pos.setY(maxY);

		// Make sure the item doesn't collide with another item
		/*QList<QGraphicsItem *> coll = collidingItems();
		if(!coll.empty())
			return this->pos();*/

		return pos;
	}

	return QGraphicsRectItem::itemChange(change, value);
}

void ChainStartItem::onDeviceChanged(InputDevice *pDevice, InputDevice *pOldDevice)
{
	setToolTip(pDevice->getName().c_str());
}

void ChainStartItem::onOutputChanged(Output *pOutput, Output *pOldOutput)
{
	// Recreate the output item
	createOutputItem();
}

void ChainStartItem::createOutputItem()
{
	// Destroy old output item
	delete m_pOutputItem;
	m_pOutputItem = 0;

	Output *pOutput = m_pChainStart->getOutput();
	if(!pOutput)
	{
		setRect(0,0, g_stdWidth, g_stdHeight);
		return;
	}

	switch(pOutput->getType())
	{
	case OT_Value:
		m_pOutputItem = new ValueOutputItem((ValueOutput *) pOutput, this);
		break;

	case OT_Range:
		m_pOutputItem = new RangeOutputItem((RangeOutput *) pOutput, this);
		break;
	};
}
