#ifndef MIDIME_CHAINITEM_H
#define MIDIME_CHAINITEM_H

// Includes
#include "global.h"
#include <QtGui/QGraphicsRectItem>

namespace MidiMe
{
	// Forward declarations
	class ChainWidget;
	class EdgeItem;

	/** The base class for input and output items. */
	class ChainItem: public QGraphicsRectItem
	{
	public:
		// Static settings
		static const float margin;
		static const float width;
		static const float height;

		// Constructors and destructor
		ChainItem(ChainWidget *pChainWidget, QGraphicsItem *pParent = 0);
		virtual ~ChainItem();

		// The connected edge
		EdgeItem *getConnectedEdge() const { return m_pConnectedEdge; }
		bool isConnected() const { return (m_pConnectedEdge != 0); }
		virtual void disconnect() = 0;

		/// The position (in scene coordinates) where to anchor an edge to
		QPointF getAnchor() const { return mapToScene(m_localAnchor); }

	protected:
		// Member variables
		ChainWidget *m_pChainWidget;
		QGraphicsRectItem *m_pMeterItem;
		QPointF m_localAnchor;
		EdgeItem *m_pConnectedEdge;
	};
}

#endif // MIDIME_CHAINITEM_H
