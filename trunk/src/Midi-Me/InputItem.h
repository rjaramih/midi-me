#ifndef MIDIME_INPUTITEM_H
#define MIDIME_INPUTITEM_H

// Includes
#include "global.h"
#include <QtGui/QGraphicsRectItem>
#include <libMidi-Me/Input.h>

namespace MidiMe
{
	// Forward declarations
	class Input;

	/** Class Description */
	class InputItem: public QGraphicsRectItem, protected Input::Listener
	{
	public:
		// Constructors and destructor
		InputItem(Input *pInput, QGraphicsItem *pParent = 0);
		virtual ~InputItem();

		// Information
		Input *getInput() const { return m_pInput; }

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

		// Input::Listener functions
		void onValue(Input *pInput, int value);

		// Member variables
		Input *m_pInput;
		QGraphicsRectItem *m_pMeterItem;
	};
}

#endif // MIDIME_INPUTITEM_H
