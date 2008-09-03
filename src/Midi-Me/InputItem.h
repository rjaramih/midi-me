#ifndef MIDIME_INPUTITEM_H
#define MIDIME_INPUTITEM_H

// Includes
#include "global.h"
#include "ChainItem.h"
#include <libMidi-Me/Input.h>

namespace MidiMe
{
	// Forward declarations
	class Input;

	/** Class Description */
	class InputItem: public ChainItem, protected Input::Listener
	{
	public:
		// Constructors and destructor
		InputItem(ChainWidget *pChainWidget, Input *pInput, QGraphicsItem *pParent = 0);
		virtual ~InputItem();

		// QGraphicsItem functions
		enum { Type = UserType + 2 };
		int type() const { return Type; }

		// Information
		Input *getInput() const { return m_pInput; }

		// The connected edge
		void disconnect();

	protected:
		// Input::Listener functions
		void onValue(Input *pInput, real value);

		// Output items can connect themselves
		void setConnectedEdge(EdgeItem *pEdge) { m_pConnectedEdge = pEdge; }
		friend class OutputItem;

		// Member variables
		Input *m_pInput;
	};
}

#endif // MIDIME_INPUTITEM_H
