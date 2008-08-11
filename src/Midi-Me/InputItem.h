#ifndef MIDIME_INPUTITEM_H
#define MIDIME_INPUTITEM_H

// Includes
#include "global.h"
#include <QtGui/QGraphicsRectItem>

namespace MidiMe
{
	// Forward declarations
	class Input;

	/** Class Description */
	class InputItem: public QGraphicsRectItem
	{
	public:
		// Constructors and destructor
		InputItem(Input *pInput, QGraphicsItem *pParent = 0);
		virtual ~InputItem();

		// Information
		Input *getInput() const { return m_pInput; }

	protected:
		// Events
		virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *pEvent);
		virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

		// Member variables
		Input *m_pInput;
	};
}

#endif // MIDIME_INPUTITEM_H
