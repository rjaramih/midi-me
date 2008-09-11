// Includes
#include "PropertiesEditor.h"
#include "PropertyWidget.h"
#include "PropertyWidgetFactory.h"

#include <Properties/Property.h>
#include <Properties/PropertyCollection.h>
#include <Properties/StandardProperties.h>

#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QTreeWidget>

using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

PropertiesEditor::PropertiesEditor(QWidget *pParent, Qt::WindowFlags flags)
: QWidget(pParent, flags)
{
	m_pTree = NULL;

	layoutGui();
}

PropertiesEditor::~PropertiesEditor()
{
	destroyPropertyWidgets();
}


/******************
* Other functions *
******************/

void PropertiesEditor::clear()
{
	destroyPropertyWidgets();
	m_pTree->clear();
}

void PropertiesEditor::addCollection(const string &name, const string &type, PropertyCollection *pProperties)
{
	// Create a new tree for this collection
	QTreeWidgetItem *pCollectionItem = new QTreeWidgetItem;
	m_pTree->invisibleRootItem()->addChild(pCollectionItem);
	m_items[name] = pCollectionItem;

	// Create a label
	pCollectionItem->setBackgroundColor(0, QColor(200, 200, 200));
	pCollectionItem->setBackgroundColor(1, QColor(200, 200, 200));
	pCollectionItem->setText(0, name.c_str());
	pCollectionItem->setText(1, type.c_str());

	// Add the properties
	if(pProperties)
	{
		m_collections[name] = pProperties;

		const PropertyList &props = pProperties->getPropertiesList();
		PropertyList::const_iterator it;
		for (it = props.begin(); it != props.end(); ++it)
		{
			Property *pProperty = *it;
			addProperty(pCollectionItem, pProperty->getName(), pProperty);
		}
	}

	// Expand the tree
	m_pTree->expandAll();

	// Add us as a listener
	pProperties->addListener(this);
}

void PropertiesEditor::removeCollection(const string &name)
{
	if(m_collections.find(name) == m_collections.end())
	{
		cerr << "[PropertiesEditor] Warning: Can't remove unknown collection '" << name << "'!" << endl;
		return;
	}

	PropertyCollection *pCollection = m_collections[name];
	if(!pCollection)
		return;

	// Remove us as a listener
	pCollection->removeListener(this);

	// Remove from the collection list
	destroyPropertyWidgets(m_collections[name]);
	m_collections.erase(name);

	// Remove the collection tree
	ItemMap::iterator it = m_items.find(name);
	if(it != m_items.end())
	{
		//m_pTree->invisibleRootItem()->removeChild(it->second);
		delete it->second;
		m_items.erase(it);
	}
}


/**********************
* Protected functions *
**********************/

void PropertiesEditor::onPropertyAdded(Property *pProperty)
{
	//! @todo Implement support for dynamic properties
}

void PropertiesEditor::onPropertyRemoving(Property *pProperty)
{
	//! @todo Implement support for dynamic properties
}

void PropertiesEditor::onPropertyChanged(Property *pProperty)
{
	assert(pProperty && m_propertyWidgets.find(pProperty) != m_propertyWidgets.end());

	// Update the corresponding widget
	m_propertyWidgets[pProperty]->updateFromProperty();
}

void PropertiesEditor::layoutGui()
{
	QGridLayout *layout = new QGridLayout(this);
	
	// create widgets
	m_pTree = new QTreeWidget(this);
	
	// layout
	layout->addWidget(m_pTree);
	
	// settings
	m_pTree->setColumnCount(2);
	m_pTree->setUniformRowHeights(false);
	m_pTree->setHeaderLabels(QStringList() << "Name" << "Value");
	m_pTree->setAlternatingRowColors(true);
	setObjectName("PropertiesEditorWidget");
}

void PropertiesEditor::addProperty(QTreeWidgetItem *pParent, const std::string &name, Property *pProperty)
{
	if(!PropertyWidgetFactory::getInstance().canCreate(pProperty->getType()))
		return;

	// Create the correct property widget
	PropertyWidget *pWidget = PropertyWidgetFactory::getInstance().createWidget(pProperty);
	assert(pWidget);

	// Create a new tree item
	QTreeWidgetItem *cur = new QTreeWidgetItem;
	pParent->addChild(cur);

	// layout
	int height = pWidget->sizeHint().height();
	cur->setText(0, name.c_str());
	m_pTree->setItemWidget(cur, 1, pWidget);
	m_propertyWidgets[pProperty] = pWidget;
	
	// settings
	pWidget->setMinimumHeight(height);
	cur->setSizeHint(0, QSize(cur->sizeHint(0).width(), height));
	
	// if compound, add child props
	if (pProperty->getType() == "compound")
	{
		CompoundProperty *pCompound = static_cast<CompoundProperty *>(pProperty);
		const PropertyMap &children = pCompound->getProperties();
		PropertyMap::const_iterator it;
		for(it = children.begin(); it != children.end(); ++it)
			addProperty(cur, it->first, it->second);
	}
}

void PropertiesEditor::destroyPropertyWidgets()
{
	PropertyWidgetMap::iterator it;
	for(it = m_propertyWidgets.begin(); it != m_propertyWidgets.end(); ++it)
		PropertyWidgetFactory::getInstance().destroyWidget(it->second);
	m_propertyWidgets.clear();
}

void PropertiesEditor::destroyPropertyWidgets(const PropertyCollection *pCollection)
{
	const PropertyList &properties = pCollection->getPropertiesList();
	PropertyList::const_iterator it;
	for(it = properties.begin(); it != properties.end(); ++it)
		destroyPropertyWidget(*it);
}

void PropertiesEditor::destroyPropertyWidget(Property *pProperty)
{
	// If compound, destroy children
	if(pProperty->getType() == "compound")
	{
		CompoundProperty *pCompound = (CompoundProperty *) pProperty;
		const PropertyMap &children = pCompound->getProperties();
		PropertyMap::const_iterator it;
		for(it = children.begin(); it != children.end(); ++it)
			destroyPropertyWidget(it->second);
	}

	// Destroy widget
	PropertyWidgetFactory::getInstance().destroyWidget(m_propertyWidgets[pProperty]);
	m_propertyWidgets.erase(pProperty);
}
