// Includes
#include "ChainItem.h"
#include "ChainWidget.h"
using namespace MidiMe;

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsSceneMouseEvent>

/// The hardcoded margin between items
const float ChainItem::margin = 5.0f;
const float ChainItem::width = 50.0f;
const float ChainItem::height = 15.0f;


/******************************
* Constructors and destructor *
******************************/

ChainItem::ChainItem(ChainWidget *pChainWidget, QGraphicsItem *pParent)
: QGraphicsRectItem(pParent), m_pChainWidget(pChainWidget), m_pMeterItem(0), m_pConnectedEdge(0)
{
	assert(m_pChainWidget);

	// Make this a top-level item if no parent is provided
	if(!pParent)
		m_pChainWidget->getScene()->addItem(this);

	// Setup item
	//setFlag(ItemIsSelectable);
	//setFlag(ItemIsMovable);
	//setFlag(ItemIsFocusable);

	setRect(0,0, width, height);
	setBrush(Qt::NoBrush);

	// Create the meter item
	m_pMeterItem = new QGraphicsRectItem(this);
	m_pMeterItem->setBrush(Qt::green);
	m_pMeterItem->setRect(0, 0, 0, height);
}

ChainItem::~ChainItem()
{
	delete m_pMeterItem;
}


/******************
* Other functions *
******************/


/**********************
* Protected functions *
**********************/
