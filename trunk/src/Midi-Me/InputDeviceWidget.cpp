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
	m_items.clear();

	if(!m_pDevice)
	{
		//m_pScene->addText("Device unplugged!");
		setWindowTitle("Midi-Me :: Device unplugged");
		return;
	}

	//m_pScene->addText(m_pDevice->getName().c_str());
	setWindowTitle(QString("Midi-Me :: ") + m_pDevice->getName().c_str());

	const OutputMap &outputs = m_pDevice->getAllOutputs();
	OutputMap::const_iterator it;
	float xDigital = 5.0f;
	float xAnalog = 5.0f;
	float yDigital = 5.0f;
	float yAnalog = 25.0f;

	for(it = outputs.begin(); it != outputs.end(); ++it)
	{
		Output *pOutput = it->second;

		QAbstractGraphicsShapeItem *pItem;
		if(pOutput->isAnalog())
		{
			QRectF rect(xAnalog, yAnalog, 15, 50);
			pItem = m_pScene->addRect(rect);
			pItem->setBrush(Qt::NoBrush);

			rect.setTop(rect.bottom());
			QGraphicsRectItem *pMeterItem = new QGraphicsRectItem(rect, pItem, m_pScene);
			pMeterItem->setBrush(Qt::green);

			xAnalog += 20.0f;
		}
		else
		{
			pItem = m_pScene->addEllipse(xDigital, yDigital, 15, 15);
			pItem->setBrush(Qt::red);

			xDigital += 20.0f;
		}

		m_items[pOutput] = pItem;
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

void InputDeviceWidget::onValue(Output *pOutput, real value)
{
	if(pOutput->isAnalog())
	{
		QGraphicsRectItem *pItem = (QGraphicsRectItem *) m_items[pOutput];
		QGraphicsRectItem *pMeterItem = (QGraphicsRectItem *) pItem->childItems().first();

		//float u = (value - pOutput->getMinValue()) / (float) (pOutput->getMaxValue() - pOutput->getMinValue());
		real u = value;
		
		QRectF rect = pItem->rect();
		rect.setTop(rect.bottom() - rect.height() * u);
		pMeterItem->setRect(rect);
	}
	else
	{
		QGraphicsEllipseItem *pItem = (QGraphicsEllipseItem *) m_items[pOutput];
		//pItem->setBrush(value == pOutput->getMinValue() ? Qt::red : Qt::green);
		pItem->setBrush(value == 1 ? Qt::red : Qt::green);
	}

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
