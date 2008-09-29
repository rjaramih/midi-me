// Includes
#include "ConnectionItem.h"
#include "ChainWidget.h"
#include "InputItem.h"
#include "OutputItem.h"
#include <libMidi-Me/Connection.h>
using namespace MidiMe;

#include <math.h>
static const double g_pi = 3.14159265358979323846264338327950288419717;
static double g_twoPi = 2.0 * g_pi;
static double g_degToRad = 0.0174532925;

static const qreal g_penWidth = 1;
static const qreal g_arrowSize = 10;
static const qreal g_margin = 5;


/******************************
* Constructors and destructor *
******************************/

ConnectionItem::ConnectionItem(ChainWidget *pChain, Connection *pConnection)
: QGraphicsItem(), m_pChainWidget(pChain), m_pConnection(pConnection)
{
	assert(m_pChainWidget);

	// On top of the other items
	setZValue(1);

	m_pChainWidget->getScene()->addItem(this);
	adjust();
}

ConnectionItem::~ConnectionItem()
{
}


/**************************
* QGraphicsItem functions *
**************************/

void ConnectionItem::paint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *pWidget)
{
	// Draw the path
	pPainter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	pPainter->drawPath(m_path);

	// Draw the arrow head
	pPainter->setBrush(Qt::black);
	pPainter->drawPolygon(m_arrow);
}


/******************
* Other functions *
******************/

InputItem *ConnectionItem::getInputItem() const
{
	if(!m_pConnection)
		return 0;

	return m_pChainWidget->getInputItem(m_pConnection->getInput());
}

OutputItem *ConnectionItem::getOutputItem() const
{
	if(!m_pConnection)
		return 0;

	return m_pChainWidget->getOutputItem(m_pConnection->getOutput());
}

/** Generate the new geometry for this edge */
void ConnectionItem::adjust()
{
	// Destroy the old path
	m_path = QPainterPath();

	// Get the items belonging to this connection
	OutputItem *pOutputItem = 0;
	if(m_pConnection)
		pOutputItem = m_pChainWidget->getOutputItem(m_pConnection->getOutput());

	InputItem *pInputItem = 0;
	if(m_pConnection)
		pInputItem = m_pChainWidget->getInputItem(m_pConnection->getInput());

	QPointF from = pOutputItem ? pOutputItem->getAnchor() : m_tempStartPos;
	QPointF to = pInputItem ? pInputItem->getAnchor() : m_tempEndPos;

	// Generate the path between the two anchors
	m_path.moveTo(from);

	QPointF c1(from + QPointF(10, 0));
	QPointF c2(from + QPointF(15, 0));
	m_path.cubicTo(c1, c2, to);

	// Generate the arrow head
	double angle = m_path.angleAtPercent(1) * g_degToRad;
	QPointF destArrowP1 = m_path.currentPosition() + QPointF(sin(angle - g_pi / 3) * g_arrowSize, cos(angle - g_pi / 3) * g_arrowSize);
	QPointF destArrowP2 = m_path.currentPosition() + QPointF(sin(angle - g_pi + g_pi / 3) * g_arrowSize, cos(angle - g_pi + g_pi / 3) * g_arrowSize);

	m_arrow.clear();
	m_arrow << m_path.currentPosition() << destArrowP1 << destArrowP2 << m_path.currentPosition();


	// Generate the bounding shape
	m_boundingShape = m_path;
	m_boundingShape.addEllipse(m_arrow.boundingRect().adjusted(-2, -2, 2, 2));

	// Calculate the bounding rect
	m_boundingRect = m_boundingShape.boundingRect();
	m_boundingRect.adjust(-g_margin, -g_margin, g_margin, g_margin);


	// Tell QT to redraw this item next time
	prepareGeometryChange();
}


/**********************
* Protected functions *
**********************/
