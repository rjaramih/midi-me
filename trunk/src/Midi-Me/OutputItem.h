#ifndef MIDIME_OUTPUTITEM_H
#define MIDIME_OUTPUTITEM_H

// Includes
#include "global.h"
#include <QtGui/QGraphicsRectItem>

namespace MidiMe
{
	// Forward declarations
	class Output;
	class ValueOutput;
	class RangeOutput;

	/** Class Description */
	class OutputItem: public QGraphicsRectItem
	{
	public:
		// Constructors and destructor
		OutputItem(QGraphicsItem *pParent = 0);
		virtual ~OutputItem();

	protected:
		// Events
		void contextMenuEvent(QGraphicsSceneContextMenuEvent *pEvent);
		QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	};

	class ValueOutputItem: public OutputItem
	{
	public:
		// Constructors and destructor
		ValueOutputItem(ValueOutput *pOutput, QGraphicsItem *pParent = 0);
		virtual ~ValueOutputItem();

		// Information
		ValueOutput *getOutput() const { return m_pOutput; }

	protected:
		// Member variables
		ValueOutput *m_pOutput;
	};

	class RangeOutputItem: public OutputItem
	{
	public:
		// Constructors and destructor
		RangeOutputItem(RangeOutput *pOutput, QGraphicsItem *pParent = 0);
		virtual ~RangeOutputItem();

		// Information
		RangeOutput *getOutput() const { return m_pOutput; }

	protected:
		// Member variables
		RangeOutput *m_pOutput;
	};
}

#endif // MIDIME_OUTPUTITEM_H
