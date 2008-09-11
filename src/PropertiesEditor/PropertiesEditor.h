#ifndef PROPERTIESEDITOR_PROPERTIESEDITOR_H
#define PROPERTIESEDITOR_PROPERTIESEDITOR_H

// Includes
#include "global.h"

#include <QtGui/QWidget>
#include <Properties/PropertyCollection.h>

#include <list>
#include <map>


// Forward declarations
class QTreeWidget;
class QTreeWidgetItem;

namespace MidiMe
{
	// Forward declarations
	class PropertyWidget;

	/** This widget can edit a property collection. */
	class PROPERTIESEDITOR_API PropertiesEditor: public QWidget, protected PropertyCollection::Listener
	{
		Q_OBJECT

	public:
		// Constructors and destructor
		PropertiesEditor(QWidget *pParent = NULL, Qt::WindowFlags flags = 0);
		virtual ~PropertiesEditor();

	public slots:
		void clear();
		void addCollection(const std::string &name, const std::string &type, PropertyCollection *pProperties);
		void removeCollection(const std::string &name);

	private:
		// PropertyCollection::Listener functions
		void onPropertyAdded(Property *pProperty);
		void onPropertyRemoving(Property *pProperty);
		void onPropertyChanged(Property *pProperty);

		// Other functions
		void layoutGui();
		void addProperty(QTreeWidgetItem *pParent, const string &name, Property *pProperty);
		void destroyPropertyWidgets();
		void destroyPropertyWidgets(const PropertyCollection *pCollection);
		void destroyPropertyWidget(Property *pProperty);

		// Member variables
		QTreeWidget *m_pTree;

		typedef std::map<string, QTreeWidgetItem *> ItemMap;
		ItemMap m_items;

		typedef std::map<string, PropertyCollection *> CollectionMap;
		CollectionMap m_collections;

		typedef std::map<Property *, PropertyWidget *> PropertyWidgetMap;
		PropertyWidgetMap m_propertyWidgets;
	};
}

#endif // PROPERTIESEDITOR_PROPERTIESEDITOR_H
