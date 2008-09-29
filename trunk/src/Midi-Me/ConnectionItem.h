#ifndef MIDIME_CONNECTIONITEM_H
#define MIDIME_CONNECTIONITEM_H

// Includes
#include "global.h"
#include <QtGui/QGraphicsItem>

namespace MidiMe
{
	// Forward declarations
	class ChainWidget;
	class Connection;
	class OutputItem;
	class InputItem;

	/** Class Description */
	class ConnectionItem: public QGraphicsItem
	{
	public:
		enum { Type = UserType + 3 };

		// Constructors and destructor
		ConnectionItem(ChainWidget *pChain, Connection *pConnection);
		virtual ~ConnectionItem();

		// Information
		ChainWidget *getChainWidget() const { return m_pChainWidget; }
		Connection *getConnection() const { return m_pConnection; }

		// Convenience functions
		OutputItem *getOutputItem() const;
		InputItem *getInputItem() const;

		// QGraphicsItem functions
		int type() const { return Type; }
		QRectF boundingRect() const { return m_boundingRect; }
		QPainterPath shape() const { return m_boundingShape; }

		/// When the edge is not fully connected yet, provide it with the temporary positions
		void setTempStartPosition(const QPointF &pos) { m_tempStartPos = pos; adjust(); }
		void setTempEndPosition(const QPointF &pos) { m_tempEndPos = pos; adjust(); }
    
		/// Adjust the geometry of the edge (call when one of the end-points move)
		void adjust();

	protected:
		// QGraphicsItem functions
		void paint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *pWidget = 0);

		// Member variables
		ChainWidget *m_pChainWidget;
		Connection *m_pConnection;
		QPointF m_tempStartPos, m_tempEndPos;

		QPainterPath m_path;
		QPolygonF m_arrow;
		QRectF m_boundingRect;
		QPainterPath m_boundingShape;
	};
}

#endif // MIDIME_CONNECTIONITEM_H
