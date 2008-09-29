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

	typedef std::map<Input *, InputItem *> InputItemMap;
	typedef std::map<Output *, OutputItem *> OutputItemMap;

	/** This widget displays the state of an input device. */
	class ProcessorItem: public QGraphicsRectItem
	{
		//Q_OBJECT

	public:
		// Constructors and destructor
		ProcessorItem(ChainWidget *pChainWidget, Processor *pProcessor, QGraphicsItem *pParent = 0);
		virtual ~ProcessorItem();

		// Input items
		const InputItemMap &getAllInputs() const { return m_inputItems; }

		// Output items
		const OutputItemMap &getAllOutputs() const { return m_outputItems; }

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

		InputItemMap m_inputItems;
		OutputItemMap m_outputItems;
	};
}

#endif // MIDIME_PROCESSORITEM_H
