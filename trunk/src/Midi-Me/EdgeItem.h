#ifndef MIDIME_EDGEITEM_H
#define MIDIME_EDGEITEM_H

// Includes
#include "global.h"
#include <QtGui/QGraphicsItem>

namespace MidiMe
{
	// Forward declarations
	class ChainWidget;
	class InputItem;
	class OutputItem;

	/** Class Description */
	class EdgeItem: public QGraphicsItem
	{
	public:
		enum { Type = UserType + 3 };

		// Constructors and destructor
		EdgeItem(ChainWidget *pChain, InputItem *pInput, OutputItem *pOutput);
		virtual ~EdgeItem();

		// Information
		ChainWidget *getChainWidget() const { return m_pChainWidget; }
		InputItem *getInputItem() const { return m_pInputItem; }
		OutputItem *getOutputItem() const { return m_pOutputItem; }

		// QGraphicsItem functions
		int type() const { return Type; }
		QRectF boundingRect() const;

		/// When the edge is not fully connected yet, provide it with the mouse position
		void setTempPosition(const QPointF &pos) { m_tempPos = pos; adjust(); }
    
		/// Adjust the geometry of the edge (call when one of the end-points move)
		void adjust();

	protected:
		// QGraphicsItem functions
		void paint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *pWidget = 0);

		// Member variables
		ChainWidget *m_pChainWidget;
		InputItem *m_pInputItem;
		OutputItem *m_pOutputItem;
		QPointF m_tempPos;
		QPainterPath *m_pPath;
	};
}

#endif // MIDIME_EDGEITEM_H
