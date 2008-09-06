// Includes
#include "PluginWidget.h"
#include <PluginSystem/Plugin.h>
#include <PluginSystem/PluginSystem.h>
using namespace MidiMe;

#include <QtCore/QDir>
#include <QtGui/QMessageBox>


/******************************
* Constructors and destructor *
******************************/

PluginWidget::PluginWidget(QWidget *pParent)
: QDialog(pParent), m_refreshing(false)
{
	// Add the designed widgets
	setupUi(this);

	// Connect signals
	connect(treePlugins, SIGNAL(itemChanged(QTreeWidgetItem *, int)), SLOT(changePlugin(QTreeWidgetItem *)));
	connect(treePlugins, SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)), SLOT(changeDescription(QTreeWidgetItem *)));

	// Refresh the plugin list
	refresh();
}

PluginWidget::~PluginWidget()
{
}


/******************
* Other functions *
******************/

void PluginWidget::refresh()
{
	m_refreshing = true;

	plugin::PluginManager *pPluginMgr = plugin::PluginSystem::getInstance().getPluginManager();
	assert(pPluginMgr);
	QString prefix = pPluginMgr->getPrefix().c_str();
	QString suffix = pPluginMgr->getSuffix().c_str();
	//! @todo We should get the extension information from the plugin system
#if defined(_WIN32_WCE) || defined(WIN32)
	suffix += ".dll";
#elif defined(__APPLE__)
	suffix += ".dylib";
#else
	suffix += ".so";
#endif

	// Clear
	treePlugins->clear();
	textDescription->clear();

	// Search the plugin dir for plugins
	QDir dir(pPluginMgr->getSearchPath().c_str());
	if(!dir.exists())
	{
		textDescription->setText("Error: The plugin search path is not found!");
		textDescription->setEnabled(false);

		m_refreshing = false;
		return;
	}

	// Generate the correct file filter
	QString nameFilter = prefix + "*" + suffix;

	// List all plugins
	//! @todo Filter pre- and postfix out of the name
	dir.setFilter(QDir::Files | QDir::Readable);
	dir.setNameFilters(QStringList() << nameFilter);

	QStringList list = dir.entryList();
	for(int i = 0; i < list.size(); ++i)
	{
		QTreeWidgetItem *pItem = new QTreeWidgetItem(treePlugins->invisibleRootItem());

		// Cut the pre- and postfix from the plugin name
		QString pluginName = list.at(i)/*.baseName()*/;
		pluginName.remove(0, prefix.length());
		pluginName.chop(suffix.length());
		pItem->setText(0, pluginName);

		// Check if the plugin is already started
		if(pPluginMgr->isStarted(pluginName.toStdString()))
			pItem->setCheckState(0, Qt::Checked);
		else
			pItem->setCheckState(0, Qt::Unchecked);
	}

	m_refreshing = false;
}


/**********************
* Protected functions *
**********************/

void PluginWidget::changePlugin(QTreeWidgetItem *pItem)
{
	if(m_refreshing) return;

	plugin::PluginManager *pPluginMgr = plugin::PluginSystem::getInstance().getPluginManager();
	assert(pPluginMgr);

	if(pItem->checkState(0) == Qt::Checked)
	{
		if(!pPluginMgr->start(pItem->text(0).toStdString()))
		{
			pItem->setCheckState(0, Qt::Unchecked);
			QMessageBox::warning(this, "Midi-Me :: Error", "The plugin failed to start");
		}
	}
	else
	{
		if(!pPluginMgr->stop(pItem->text(0).toStdString()))
		{
			pItem->setCheckState(0, Qt::Checked);
			QMessageBox::warning(this, "Midi-Me :: Error", "The plugin failed to stop");
		}
	}
}

void PluginWidget::changeDescription(QTreeWidgetItem *pItem)
{
	if(m_refreshing) return;

	if(!pItem)
	{
		textDescription->setText("Plugin description");
		textDescription->setEnabled(false);
		return;
	}

	/** @todo Change plugin system so it creates the plugins separately from starting them,
		then we can ask for their description (and dependency information)
	*/

	plugin::PluginManager *pPluginMgr = plugin::PluginSystem::getInstance().getPluginManager();
	assert(pPluginMgr);

	string pluginName = pItem->text(0).toStdString();
	if(pPluginMgr->isStarted(pluginName))
	{
		string description = pPluginMgr->getPlugin(pluginName)->getDescription();
		if(description.empty())
		{
			textDescription->setText("No description available");
			textDescription->setEnabled(false);
		}
		else
		{
			textDescription->setText(description.c_str());
			textDescription->setEnabled(true);
		}
	}
}
