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
	// Setup window geometry
	setWindowFlags(Qt::Tool);

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
		m_pScene->addText("Device unplugged!");
		return;
	}

	m_pScene->addText(m_pDevice->getName().c_str());

	for(unsigned int i = 0; i < m_pDevice->numValueOutputs(); ++i)
	{
		QGraphicsEllipseItem *pItem = m_pScene->addEllipse(i * 20, 20, 15, 15);
		pItem->setBrush(Qt::red);
		m_valueItems[m_pDevice->getValueOutput(i)] = pItem;
	}

	for(unsigned int i = 0; i < m_pDevice->numRangeOutputs(); ++i)
	{
		QGraphicsRectItem *pItem = m_pScene->addRect(i * 20, 40, 15, 50);
		pItem->setBrush(Qt::red);
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
	m_rangeItems[pOutput]->setBrush(QColor::fromRgbF(1.0f - u, u, 0));
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
