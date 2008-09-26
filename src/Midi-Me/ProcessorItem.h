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
	class PropertiesEditor;
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
		void createInputs();
		void destroyInputs();

		void createOutputs();
		void destroyOutputs();

		void createInfo();
		void destroyInfo();

		void adjustPosition(QPointF &position);
		QGraphicsScene *getScene() const;

		// Member variables
		ChainWidget *m_pChainWidget;
		PropertiesEditor *m_pPropertyEditor;
		Processor *m_pProcessor;

		typedef std::map<Input *, InputItem *> InputItemMap;
		InputItemMap m_inputItems;

		typedef std::map<Output *, OutputItem *> OutputItemMap;
		OutputItemMap m_outputItems;
	};
}

#endif // MIDIME_PROCESSORITEM_H
