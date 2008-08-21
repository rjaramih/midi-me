#ifndef MIDIME_OUTPUTITEM_H
#define MIDIME_OUTPUTITEM_H

// Includes
#include "global.h"
#include <QtGui/QGraphicsRectItem>
#include <libMidi-Me/Output.h>

// Forward declarations
class QGraphicsSceneMouseEvent;

namespace MidiMe
{
	// Forward declarations
	class Output;

	/** Class Description */
	class OutputItem: public QGraphicsRectItem, protected Output::Listener
	{
	public:
		// Constructors and destructor
		OutputItem(Output *pOutput, QGraphicsItem *pParent = 0);
		virtual ~OutputItem();

		// Information
		Output *getOutput() const { return m_pOutput; }

	protected:
		// Events
		void contextMenuEvent(QGraphicsSceneContextMenuEvent *pEvent);
		QVariant itemChange(GraphicsItemChange change, const QVariant &value);
		
		// Drag-and-drop
		void mousePressEvent(QGraphicsSceneMouseEvent *pEvent);
		void dragEnterEvent(QGraphicsSceneDragDropEvent *pEvent);
		void dragMoveEvent(QGraphicsSceneDragDropEvent *pEvent);
		void dragLeaveEvent(QGraphicsSceneDragDropEvent *pEvent);
		void dropEvent(QGraphicsSceneDragDropEvent *pEvent);

		// Output::Listener functions
		void onValue(Output *pOutput, int value);

		// Member variables
		Output *m_pOutput;
		QGraphicsRectItem *m_pMeterItem;
	};
}

#endif // MIDIME_OUTPUTITEM_H
