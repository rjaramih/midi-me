#ifndef MIDIME_CHAINENDITEM_H
#define MIDIME_CHAINSTARTITEM_H

// Includes
#include "global.h"
#include <QtGui/QGraphicsRectItem>
#include <libMidi-Me/ChainEnd.h>

// Forward declarations
class QAction;

namespace MidiMe
{
	// Forward declarations
	class InputItem;

	/** Class Description */
	class ChainEndItem: public QObject, public QGraphicsRectItem, protected ChainEnd::Listener
	{
		Q_OBJECT

	public:
		// Constructors and destructor
		ChainEndItem(ChainEnd *pChainEnd, QGraphicsItem *pParent = 0);
		virtual ~ChainEndItem();

		// Other functions
    
	public slots:
		void showSettings();

	protected:
		// Events
		void contextMenuEvent(QGraphicsSceneContextMenuEvent *pEvent);
		QVariant itemChange(GraphicsItemChange change, const QVariant &value);

		// ChainEnd::Listener functions
		void onMidiChanged(MidiOutput *pMidi, MidiOutput *pOldMidi);
		void onInputChanged(Input *pInput, Input *pOldInput);

		// Other functions
		void createInputItem();

		// Member variables
		ChainEnd *m_pChainEnd;
		InputItem *m_pInputItem;
	};
}

#endif // MIDIME_CHAINSTARTITEM_H
