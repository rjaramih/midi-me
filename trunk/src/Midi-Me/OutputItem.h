#ifndef MIDIME_OUTPUTITEM_H
#define MIDIME_OUTPUTITEM_H

// Includes
#include "global.h"
#include <QtGui/QGraphicsRectItem>

namespace MidiMe
{
	// Forward declarations
	class Output;

	/** Class Description */
	class OutputItem: public QGraphicsRectItem
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

		// Member variables
		Output *m_pOutput;
	};
}

#endif // MIDIME_OUTPUTITEM_H
