#ifndef MIDIME_CHAINENDITEM_H
#define MIDIME_CHAINSTARTITEM_H

// Includes
#include "global.h"
#include "InputItem.h"
#include <libMidi-Me/ChainEnd.h>

// Forward declarations
class QAction;

namespace MidiMe
{
	// Forward declarations
	class InputItem;
	class PropertiesEditor;

	/** Class Description */
	class ChainEndItem: public InputItem
	{
		Q_OBJECT

	public:
		// Constructors and destructor
		ChainEndItem(ChainWidget *pChainWidget, ChainEnd *pChainEnd, QGraphicsItem *pParent = 0);
		virtual ~ChainEndItem();

		// Properties
		PropertiesEditor *getPropertyEditor() const { return m_pPropertyEditor; }
		void setPropertyEditor(PropertiesEditor *pEditor) { m_pPropertyEditor = pEditor; }

		// Other functions
		void adjustPosition();

	protected:
		// Events
		void mousePressEvent(QGraphicsSceneMouseEvent *pEvent);
		QVariant itemChange(GraphicsItemChange change, const QVariant &value);

		// Other functions
		void adjustPosition(QPointF &position);

		// Member variables
		ChainEnd *m_pChainEnd;
		PropertiesEditor *m_pPropertyEditor;
	};
}

#endif // MIDIME_CHAINSTARTITEM_H
