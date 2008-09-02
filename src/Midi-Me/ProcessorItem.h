#ifndef MIDIME_PROCESSORITEM_H
#define MIDIME_PROCESSORITEM_H

// Includes
#include "global.h"
#include <QtGui/QGraphicsRectItem>
#include <map>

// Forward declarations
class QGraphicsScene;

namespace MidiMe
{
	// Forward declarations
	class ChainWidget;
	class Processor;
	class Input; class InputItem;
	class Output; class OutputItem;

	/** This widget displays the state of an input device. */
	class ProcessorItem: public QGraphicsRectItem
	{
		//Q_OBJECT

	public:
		// Constructors and destructor
		ProcessorItem(ChainWidget *pChainWidget, Processor *pProcessor, QGraphicsItem *pParent = 0);
		virtual ~ProcessorItem();

		// Other functions
		void adjustPosition();

	protected:
		// Events
		void contextMenuEvent(QGraphicsSceneContextMenuEvent *pEvent);
		QVariant itemChange(GraphicsItemChange change, const QVariant &value);

		// Other functions
		void createInputs();
		void destroyInputs();

		void createOutputs();
		void destroyOutputs();

		void adjustPosition(QPointF &position);
		QGraphicsScene *getScene() const;

		// Member variables
		ChainWidget *m_pChainWidget;
		Processor *m_pProcessor;

		typedef std::map<Input *, InputItem *> InputItemMap;
		InputItemMap m_inputItems;

		typedef std::map<Output *, OutputItem *> OutputItemMap;
		OutputItemMap m_outputItems;
	};
}

#endif // MIDIME_PROCESSORITEM_H
