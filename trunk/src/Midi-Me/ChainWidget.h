#ifndef MIDIME_CHAINWIDGET_H
#define MIDIME_CHAINWIDGET_H

// Includes
#include "global.h"
#include <libMidi-Me/Chain.h>
#include <QtGui/QGraphicsView>
#include <map>

// Forward declarations
class QGraphicsScene;
class QMenu;

namespace MidiMe
{
	// Forward declarations
	class MainWindow;
	class Chain;
	class ChainStartItem;
	class ChainEndItem;
	class ProcessorItem;
	class ChainItem;
	class OutputItem;
	class InputItem;
	class ConnectionItem;

	/** This widget displays the state of an input device. */
	class ChainWidget: public QGraphicsView, protected Chain::Listener
	{
		Q_OBJECT

	public:
		enum State { State_Normal, State_Connecting, State_Moving };

		// Constructors and destructor
		ChainWidget(Chain *pChain, MainWindow *pWindow);
		virtual ~ChainWidget();

		// Information
		QGraphicsScene *getScene() const { return m_pScene; }
		Chain *getChain() const { return m_pChain; }
		State getState() const { return m_state; }

		InputItem *getInputItem(Input *pInput) const;
		OutputItem *getOutputItem(Output *pOutput) const;
		ConnectionItem *getConnectionItem(Connection *pConnection) const;

		static QList<QGraphicsItem *> getColliders(const QGraphicsItem *pItem);

	public slots:
		void update();
		void startConnecting(const QPointF &mousePos);
		void stopConnecting(const QPointF &mousePos);

		void addControlSignal();
    
	protected slots:
		void addChainStart(QAction *pAction);
		void addProcessor(QAction *pAction);

	protected:
		// Events
		void resizeEvent(QResizeEvent *pEvent);
		void mousePressEvent(QMouseEvent *pEvent);
		void mouseReleaseEvent(QMouseEvent *pEvent);
		void mouseMoveEvent(QMouseEvent *pEvent);

		// Chain::Listener functions
		void onStartAdded(ChainStart *pStart);
		void onStartRemoving(ChainStart *pStart);
		void onEndAdded(ChainEnd *pEnd);
		void onEndRemoving(ChainEnd *pEnd);
		void onProcessorAdded(Processor *pProcessor);
		void onProcessorRemoving(Processor *pProcessor);
		void onConnectionAdded(Connection *pConnection);
		void onConnectionRemoving(Connection *pConnection);
		void onInputAdded(Input *pInput) {}
		void onInputRemoving(Input *pInput) {}
		void onOutputAdded(Output *pOutput) {}
		void onOutputRemoving(Output *pOutput) {}

		// Other functions
		void destroyItems();
		void generateChainStartMenu(QMenu *pParent);
		void generateProcessorMenu(QMenu *pParent);
		void generateChainEndMenu(QMenu *pParent);

		void distributeStartItems();
		void distributeEndItems();
		void distributeProcessorItems();

		// Member variables
		MainWindow *m_pWindow;
		QGraphicsScene *m_pScene;
		Chain *m_pChain;
		State m_state;

		typedef std::map<ChainStart *, ChainStartItem *> StartItemMap;
		StartItemMap m_startItems;

		typedef std::map<ChainEnd *, ChainEndItem *> EndItemMap;
		EndItemMap m_endItems;

		typedef std::map<Processor *, ProcessorItem *> ProcessorItemMap;
		ProcessorItemMap m_processorItems;

		typedef std::map<Input *, InputItem *> InputItemMap;
		InputItemMap m_inputItems;

		typedef std::map<Output *, OutputItem *> OutputItemMap;
		OutputItemMap m_outputItems;

		typedef std::map<Connection *, ConnectionItem *> ConnectionItemMap;
		ConnectionItemMap m_connectionItems;

		ConnectionItem *m_pTempConnection;
		OutputItem *m_pConnectingOutput;
		InputItem *m_pConnectingInput;
	};
}

#endif // MIDIME_CHAINWIDGET_H
