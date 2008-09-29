#ifndef MIDIME_OUTPUTITEM_H
#define MIDIME_OUTPUTITEM_H

// Includes
#include "global.h"
#include "ChainItem.h"
#include <libMidi-Me/Output.h>

namespace MidiMe
{
	// Forward declarations
	class Output;
	class ConnectionItem;

	/** Class Description */
	class OutputItem: public ChainItem, protected Output::Listener
	{
	public:
		// Constructors and destructor
		OutputItem(ChainWidget *pChainWidget, Output *pOutput, QGraphicsItem *pParent = 0);
		virtual ~OutputItem();

		// QGraphicsItem functions
		enum { Type = UserType + 1 };
		int type() const { return Type; }

		// Information
		Output *getOutput() const { return m_pOutput; }
		bool isConnected() const;
		ConnectionItem *getConnectionItem() const;

	protected:
		// Events
		QVariant itemChange(GraphicsItemChange change, const QVariant &value);

		// Output::Listener functions
		void onValue(Output *pOutput, real value);

		// Member variables
		Output *m_pOutput;
	};
}

#endif // MIDIME_OUTPUTITEM_H
