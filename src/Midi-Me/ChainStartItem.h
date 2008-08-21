#ifndef MIDIME_CHAINSTARTITEM_H
#define MIDIME_CHAINSTARTITEM_H

// Includes
#include "global.h"
#include "OutputItem.h"
#include <libMidi-Me/ChainStart.h>

// Forward declarations
class QAction;

namespace MidiMe
{
	// Forward declarations
	class OutputItem;

	/** Class Description */
	class ChainStartItem: public QObject, public OutputItem
	{
		Q_OBJECT

	public:
		// Constructors and destructor
		ChainStartItem(ChainStart *pChainStart, QGraphicsItem *pParent = 0);
		virtual ~ChainStartItem();

		// Other functions
    
	protected:
		// Events
		void contextMenuEvent(QGraphicsSceneContextMenuEvent *pEvent);
		QVariant itemChange(GraphicsItemChange change, const QVariant &value);

		// Member variables
		ChainStart *m_pChainStart;
	};
}

#endif // MIDIME_CHAINSTARTITEM_H
