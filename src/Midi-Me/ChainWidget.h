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
	class Chain;
	class ChainStartItem;

	/** This widget displays the state of an input device. */
	class ChainWidget: public QGraphicsView, protected Chain::Listener
	{
		Q_OBJECT

	public:
		// Constructors and destructor
		ChainWidget(Chain *pChain, QWidget *pParent = 0);
		virtual ~ChainWidget();

	public slots:
		void update();
    
	protected slots:
		void addChainStart(QAction *pAction);
		void addChainEnd(QAction *pAction);
		void addProcessor(QAction *pAction);

	protected:
		// Events
		void resizeEvent(QResizeEvent *pEvent);
		void contextMenuEvent(QContextMenuEvent *pEvent);

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

		// Member variables
		QGraphicsScene *m_pScene;
		Chain *m_pChain;

		typedef std::map<ChainStart *, ChainStartItem *> StartItemMap;
		StartItemMap m_startItems;

		typedef std::map<ChainEnd *, QGraphicsRectItem *> EndItemMap;
		EndItemMap m_endItems;

		typedef std::map<Processor *, QGraphicsRectItem *> ProcessorItemMap;
		ProcessorItemMap m_processorItems;
	};
}

#endif // MIDIME_CHAINWIDGET_H
