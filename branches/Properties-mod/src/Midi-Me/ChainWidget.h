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
	class EdgeItem;

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

	public slots:
		void update();
		void startConnecting(const QPointF &mousePos);
		void stopConnecting(const QPointF &mousePos);

		void addControlSignal();
    
	protected slots:
		void addChainStart(QAction *pAction);
		void addChainEnd(QAction *pAction);
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

		// Other functions
		void destroyItems();
		void generateChainStartMenu(QMenu *pParent);
		void generateProcessorMenu(QMenu *pParent);
		void generateChainEndMenu(QMenu *pParent);

		void distributeStartItems();
		void distributeEndItems();
		void distributeProcessorItems();

		// Output items can create and destroy edges
		EdgeItem *createEdge(OutputItem *pOutput, InputItem *pInput);
		void destroyEdge(EdgeItem *pEdge);
		friend class OutputItem;

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

		typedef std::set<EdgeItem *> EdgeItemSet;
		EdgeItemSet m_edgeItems;

		EdgeItem *m_pConnectingEdge;
	};
}

#endif // MIDIME_CHAINWIDGET_H
