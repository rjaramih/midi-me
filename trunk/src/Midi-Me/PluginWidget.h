#ifndef MIDIME_PLUGINWIDGET_H
#define MIDIME_PLUGINWIDGET_H

// Includes
#include "global.h"
#include "PluginWidgetBase.h"
#include <QtGui/QDialog>

// Forward declarations
class QtreeWidgetItem;

namespace MidiMe
{
	// Forward declarations

	/** This widget is used to manage which plugins are loaded.
		@todo Add listeners to plugin system, make this widget one.
	*/
	class PluginWidget: public QDialog, private Ui::PluginWidgetBase
	{
		Q_OBJECT

	public:
		// Constructors and destructor
		PluginWidget(QWidget *pParent = 0);
		virtual ~PluginWidget();

		// Other functions

	public slots:
		void refresh();

	protected slots:
		void changePlugin(QTreeWidgetItem *pItem);
		void changeDescription(QTreeWidgetItem *pItem);
    
	protected:
		// Member variables
		bool m_refreshing;
	};
}

#endif // MIDIME_PLUGINWIDGET_H
