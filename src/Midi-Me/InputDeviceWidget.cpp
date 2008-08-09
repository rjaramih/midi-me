// Includes
#include "InputDeviceWidget.h"
#include <libMidi-Me/InputDevice.h>
#include <libMidi-Me/Output.h>
using namespace MidiMe;

#include <QtGui/QGraphicsScene>
#include <QtGui/QResizeEvent>
#include <QtGui/QGraphicsEllipseItem>
#include <QtGui/QGraphicsRectItem>


/******************************
* Constructors and destructor *
******************************/

InputDeviceWidget::InputDeviceWidget(InputDevice *pDevice, QWidget *pParent)
: QGraphicsView(pParent), m_pDevice(pDevice)
{
	assert(m_pDevice);

	m_pScene = new QGraphicsScene(this);
	setScene(m_pScene);

	update();

	m_pDevice->addListener(this);
	DeviceManager::getInstance().addListener(this); // TEMP
}

InputDeviceWidget::~InputDeviceWidget()
{
	DeviceManager::getInstance().removeListener(this); // TEMP
	if(m_pDevice)
		m_pDevice->removeListener(this);
	delete m_pScene;
}


/******************
* Other functions *
******************/

void InputDeviceWidget::update()
{
	// Clear the current scene
	m_pScene->clear();
	m_valueItems.clear();
	m_rangeItems.clear();

	if(!m_pDevice)
	{
		//m_pScene->addText("Device unplugged!");
		setWindowTitle("Midi-Me :: Device unplugged");
		return;
	}

	//m_pScene->addText(m_pDevice->getName().c_str());
	setWindowTitle(QString("Midi-Me :: ") + m_pDevice->getName().c_str());

	for(unsigned int i = 0; i < m_pDevice->numValueOutputs(); ++i)
	{
		QGraphicsEllipseItem *pItem = m_pScene->addEllipse(5 + i * 20, 5, 15, 15);
		pItem->setBrush(Qt::red);
		m_valueItems[m_pDevice->getValueOutput(i)] = pItem;
	}

	for(unsigned int i = 0; i < m_pDevice->numRangeOutputs(); ++i)
	{
		//QList<QGraphicsItem *> items;

		// Bounding rectangle
		QRectF rect(5 + i * 20, 25, 15, 50);
		QGraphicsRectItem *pItem = m_pScene->addRect(rect);
		pItem->setBrush(Qt::NoBrush);
		//items.push_back(pItem);

		// Meter rectangle
		//pItem = m_pScene->addRect(i * 20, 40, 15, 0);
		rect.setTop(rect.bottom());
		QGraphicsRectItem *pMeterItem = new QGraphicsRectItem(rect, pItem, m_pScene);
		pMeterItem->setBrush(Qt::green);
		//items.push_back(pItem);

		// Group the items
		/*QGraphicsItemGroup *pGroup = m_pScene->createItemGroup(items);
		m_rangeItems[m_pDevice->getRangeOutput(i)] = pGroup;*/

		m_rangeItems[m_pDevice->getRangeOutput(i)] = pItem;
	}
}


/**********************
* Protected functions *
**********************/

void InputDeviceWidget::resizeEvent(QResizeEvent *pEvent)
{
	// Resize to size of the widget
	setSceneRect(0,0, pEvent->size().width(), pEvent->size().height());

	QGraphicsView::resizeEvent(pEvent);
}

void InputDeviceWidget::onValueStart(ValueOutput *pOutput)
{
	m_valueItems[pOutput]->setBrush(Qt::green);
}

void InputDeviceWidget::onValueStop(ValueOutput *pOutput)
{
	m_valueItems[pOutput]->setBrush(Qt::red);
}

void InputDeviceWidget::onValueChanged(RangeOutput *pOutput, int value)
{
	float u = (value - pOutput->getMinValue()) / (float) (pOutput->getMaxValue() - pOutput->getMinValue());
	QGraphicsRectItem *pItem = (QGraphicsRectItem *) m_rangeItems[pOutput]->childItems().first();

	QRectF rect = m_rangeItems[pOutput]->rect();
	//rect.setTop(rect.height() * u);
	rect.setTop(rect.bottom() - rect.height() * u);
	pItem->setRect(rect);
}

// TEMP
void InputDeviceWidget::onDeviceAdded(InputDevice *pDevice)
{
}

void InputDeviceWidget::onDeviceRemoving(InputDevice *pDevice)
{
	if(pDevice == m_pDevice)
		m_pDevice = 0;
}
