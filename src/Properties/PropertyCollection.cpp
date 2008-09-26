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

#if 0
void PropertyCollection::clearProperties()
{
	// Destroy the 
	// Notify the listeners of the removing properties
	PropertyList::iterator it;
	for(it = m_propertiesList.begin(); it != m_propertiesList.end(); ++it)
		fireRemoving(*it);

	m_propertiesList.clear();
	m_propertiesMap.clear();
	m_clearing = false;
}
#endif


/**********************
* Protected functions *
**********************/

void PropertyCollection::addProperty(Property *pProperty)
{
	assert(pProperty);

	m_propertiesList.push_back(pProperty);
	m_propertiesMap[pProperty->getName()] = pProperty;

	fireAdded(pProperty);
}

void PropertyCollection::removeProperty(Property *pProperty)
{
	assert(pProperty);

	fireRemoving(pProperty);

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
