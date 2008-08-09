#ifndef MIDIME_CHAINSTARTITEM_H
#define MIDIME_CHAINSTARTITEM_H

// Includes
#include "global.h"
#include <QtGui/QGraphicsRectItem>
#include <libMidi-Me/ChainStart.h>

// Forward declarations
class QAction;

namespace MidiMe
{
	// Forward declarations
	class OutputItem;

	/** Class Description */
	class ChainStartItem: public QObject, public QGraphicsRectItem, protected ChainStart::Listener
	{
		Q_OBJECT

	public:
		// Constructors and destructor
		ChainStartItem(ChainStart *pChainStart, QGraphicsItem *pParent = 0);
		virtual ~ChainStartItem();

		// Other functions
    
	protected slots:
		void selectDevice(QAction *pAction);
		void selectValueOutput(QAction *pAction);
		void selectRangeOutput(QAction *pAction);

	protected:
		// Events
		void contextMenuEvent(QGraphicsSceneContextMenuEvent *pEvent);
		QVariant itemChange(GraphicsItemChange change, const QVariant &value);

		// ChainStart::Listener functions
		void onDeviceChanged(InputDevice *pDevice, InputDevice *pOldDevice);
		void onOutputChanged(Output *pOutput, Output *pOldOutput);

		// Other functions
		void createOutputItem();

		// Member variables
		ChainStart *m_pChainStart;
		OutputItem *m_pOutputItem;
	};
}

#endif // MIDIME_CHAINSTARTITEM_H
