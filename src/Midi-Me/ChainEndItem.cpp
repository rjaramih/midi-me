// Includes
#include "ChainEndItem.h"
#include "InputItem.h"
#include <libMidi-Me/ChainEnd.h>
#include <libMidi-Me/Input.h>
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

ChainEndItem::ChainEndItem(ChainEnd *pChainEnd, QGraphicsItem *pParent)
: QGraphicsRectItem(pParent), m_pChainEnd(pChainEnd), m_pInputItem(0)
{
	assert(m_pChainEnd);

	// Setup item
	setFlag(ItemIsSelectable);
	setFlag(ItemIsMovable);
	setFlag(ItemIsFocusable);

	createInputItem();
	m_pChainEnd->addListener(this);
}

ChainEndItem::~ChainEndItem()
{
	m_pChainEnd->removeListener(this);
	delete m_pInputItem;
}


/******************
* Other functions *
******************/

void ChainEndItem::showSettings()
{
}


/**********************
* Protected functions *
**********************/

void ChainEndItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *pEvent)
{
	DeviceManager &devMgr = DeviceManager::getInstance();
	MidiOutput *pMidi = m_pChainEnd->getMidi();

	// Generate the context menu
	QMenu *pMenu = new QMenu(scene()->views().first());

	pMenu->addAction("Settings...", this, SLOT(showSettings()));
	
	pMenu->popup(pEvent->screenPos());
	pEvent->accept();
}

QVariant ChainEndItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if(change == ItemPositionChange)
	{
		assert(scene() && scene()->views().size() == 1);
		QGraphicsView *pView = scene()->views().first();

		QPointF pos = value.toPointF();

		// Make sure the item stays at the right edge
		pos.setX(pView->sceneRect().right() - rect().width() + 1.0f);

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

void ChainEndItem::onMidiChanged(MidiOutput *pMidi, MidiOutput *pOldMidi)
{
}

void ChainEndItem::onInputChanged(Input *pInput, Input *pOldInput)
{
	// Recreate the input item
	createInputItem();
}

void ChainEndItem::createInputItem()
{
	// Destroy old output item
	delete m_pInputItem;
	m_pInputItem = 0;

	Input *pInput = m_pChainEnd->getInput();
	if(!pInput)
	{
		setRect(0,0, g_stdWidth, g_stdHeight);
		return;
	}

	m_pInputItem = new InputItem(pInput, this);
}
