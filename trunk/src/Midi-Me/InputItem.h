#ifndef MIDIME_INPUTITEM_H
#define MIDIME_INPUTITEM_H

// Includes
#include "global.h"
#include <QtGui/QGraphicsRectItem>

namespace MidiMe
{
	// Forward declarations
	class Input;
	class ValueInput;
	class RangeInput;

	/** Class Description */
	class InputItem: public QGraphicsRectItem
	{
	public:
		// Constructors and destructor
		InputItem(QGraphicsItem *pParent = 0);
		virtual ~InputItem();

	protected:
		// Events
		virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *pEvent);
		virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	};

	class ValueInputItem: public InputItem
	{
	public:
		// Constructors and destructor
		ValueInputItem(ValueInput *pInput, QGraphicsItem *pParent = 0);
		virtual ~ValueInputItem();

		// Information
		ValueInput *getInput() const { return m_pInput; }

	protected:
		// Member variables
		ValueInput *m_pInput;
	};

	class RangeInputItem: public InputItem
	{
	public:
		// Constructors and destructor
		RangeInputItem(RangeInput *pInput, QGraphicsItem *pParent = 0);
		virtual ~RangeInputItem();

		// Information
		RangeInput *getInput() const { return m_pInput; }

	protected:
		// Member variables
		RangeInput *m_pInput;
	};
}

#endif // MIDIME_INPUTITEM_H
