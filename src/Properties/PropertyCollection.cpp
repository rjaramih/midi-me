// Includes
#include "PropertyCollection.h"
#include "Property.h"
#include <algorithm>
using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

PropertyCollection::PropertyCollection()
{
}

PropertyCollection::~PropertyCollection()
{
	clearProperties();
}


/*************
* Properties *
*************/

Property *PropertyCollection::getProperty(const string &name) const
{
	PropertyMap::const_iterator it = m_propertiesMap.find(name);
	return (it == m_propertiesMap.end()) ? 0 : it->second;
}

void PropertyCollection::setProperty(const string &name, const string &value)
{
	Property *pProperty = getProperty(name);
	if(pProperty)
		pProperty->fromString(value);
}


/******************
* Other functions *
******************/

void PropertyCollection::clearProperties()
{
	// Notify the listeners of the removing properties
	PropertyList::iterator it;
	for(it = m_propertiesList.begin(); it != m_propertiesList.end(); ++it)
		fireRemoving(*it);

	m_propertiesList.clear();
	m_propertiesMap.clear();
}


/**********************
* Protected functions *
**********************/

void PropertyCollection::addProperty(Property *pProperty)
{
	if(!pProperty) return;

	m_propertiesList.push_back(pProperty);
	m_propertiesMap[pProperty->getName()] = pProperty;

	pProperty->setCollection(this);
	fireAdded(pProperty);
}

void PropertyCollection::removeProperty(Property *pProperty)
{
	if(!pProperty) return;

	fireRemoving(pProperty);
	pProperty->setCollection(0);

	m_propertiesMap.erase(pProperty->getName());
	m_propertiesList.remove(pProperty);
}

void PropertyCollection::fireAdded(Property *pProperty)
{
	// The property should be part of this collection
	assert(pProperty && m_propertiesMap.find(pProperty->getName()) != m_propertiesMap.end());

	// Notify the listeners
	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onPropertyAdded(pProperty);
}

void PropertyCollection::fireRemoving(Property *pProperty)
{
	// The property should be part of this collection
	assert(pProperty && m_propertiesMap.find(pProperty->getName()) != m_propertiesMap.end());

	// Notify the listeners
	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onPropertyRemoving(pProperty);
}

void PropertyCollection::fireChanged(Property *pProperty)
{
	// The property should be part of this collection
	assert(pProperty && m_propertiesMap.find(pProperty->getName()) != m_propertiesMap.end());

	// Notify the listeners
	ListenerSet::iterator it;
	for(it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->onPropertyChanged(pProperty);
}
