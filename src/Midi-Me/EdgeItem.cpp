// Includes
#include "EdgeItem.h"
#include "ChainWidget.h"
#include "InputItem.h"
#include "OutputItem.h"
using namespace MidiMe;

#include <math.h>
static const double g_pi = 3.14159265358979323846264338327950288419717;
static double g_twoPi = 2.0 * g_pi;
static double g_degToRad = 0.0174532925;

static const qreal g_penWidth = 1;
static const qreal g_arrowSize = 10;


/******************************
* Constructors and destructor *
******************************/

EdgeItem::EdgeItem(ChainWidget *pChain, InputItem *pInput, OutputItem *pOutput)
: QGraphicsItem(), m_pChainWidget(pChain), m_pInputItem(pInput), m_pOutputItem(pOutput), m_pPath(0)
{
	assert(m_pChainWidget);

	// On top of the other items
	setZValue(1);

	m_pChainWidget->getScene()->addItem(this);
	adjust();
}

EdgeItem::~EdgeItem()
{
}


/**************************
* QGraphicsItem functions *
**************************/

QRectF EdgeItem::boundingRect() const
{
	return m_pPath->boundingRect();

	/*QPointF from = m_pOutputItem ? mapFromScene(m_pOutputItem->getAnchor()) : m_tempPos;
	QPointF to = m_pInputItem ? mapFromScene(m_pInputItem->getAnchor()) : m_tempPos;
	qreal extra = (g_penWidth + g_arrowSize) / 2.0;

	float minX = min(from.x() - extra, to.x() - extra);
	float maxX = max(from.x() + extra, to.x() + extra);
	float minY = min(from.y() - extra, to.y() - extra);
	float maxY = max(from.y() + extra, to.y() + extra);
	return QRectF(minX, minY, maxX - minX, maxY - minY);*/
}

void EdgeItem::paint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *pWidget)
{
	assert(m_pPath);

	// Draw the path
	pPainter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	pPainter->drawPath(*m_pPath);

	// Draw the arrow head
	double angle = m_pPath->angleAtPercent(1) * g_degToRad;
	QPointF destArrowP1 = m_pPath->currentPosition() + QPointF(sin(angle - g_pi / 3) * g_arrowSize, cos(angle - g_pi / 3) * g_arrowSize);
	QPointF destArrowP2 = m_pPath->currentPosition() + QPointF(sin(angle - g_pi + g_pi / 3) * g_arrowSize, cos(angle - g_pi + g_pi / 3) * g_arrowSize);
	
	pPainter->setBrush(Qt::black);
	pPainter->drawPolygon(QPolygonF() << m_pPath->currentPosition() << destArrowP1 << destArrowP2);
}


/******************
* Other functions *
******************/

/** Generate the new geometry for this edge */
void EdgeItem::adjust()
{
	// Destroy the old path
	delete m_pPath;
	m_pPath = new QPainterPath;

	QPointF from = m_pOutputItem ? m_pOutputItem->getAnchor() : m_tempPos;
	QPointF to = m_pInputItem ? m_pInputItem->getAnchor() : m_tempPos;

	// Generate the path between the two anchors
	m_pPath->moveTo(from);

	QPointF c1(from + QPointF(10, 0));
	QPointF c2(from + QPointF(15, 0));
	m_pPath->cubicTo(c1, c2, to);

	// Tell QT to redraw this item next time
	prepareGeometryChange();
}


/**********************
* Protected functions *
**********************/
