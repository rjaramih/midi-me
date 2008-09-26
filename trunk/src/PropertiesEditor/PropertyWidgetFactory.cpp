// Includes
#include "PropertyWidgetFactory.h"
#include "PropertyWidget.h"
#include "PropertyWidgetCreator.h"
#include "PropertyWidgetBool.h"
#include "PropertyWidgetCompound.h"
#include "PropertyWidgetInt.h"
#include "PropertyWidgetUInt.h"
#include "PropertyWidgetReal.h"
#include "PropertyWidgetString.h"
#include <Properties/Property.h>

using namespace MidiMe;


/************
* Singleton *
************/

PropertyWidgetFactory & PropertyWidgetFactory::getInstance()
{
	static PropertyWidgetFactory instance;
	static bool initialized = false;

	if(!initialized)
	{
		initialized = true;
		instance.createStandardWidgetCreators();
	}
	
	return instance;
}


/******************************
* Constructors and destructor *
******************************/

PropertyWidgetFactory::PropertyWidgetFactory()
{
}

PropertyWidgetFactory::~PropertyWidgetFactory()
{
}


/******************
* Other functions *
******************/

PropertyWidgetCreator * PropertyWidgetFactory::getCreator(const std::string &type) const
{
	WidgetCreatorMap::const_iterator it = m_creators.find(type);
	
	return (it == m_creators.end()) ? NULL : it->second;
}

bool PropertyWidgetFactory::canCreate(const std::string &type) const
{
	return m_creators.find(type) != m_creators.end();
}

PropertyWidget * PropertyWidgetFactory::createWidget(Property *property)
{
	PropertyWidgetCreator *pCreator = getCreator(property->getType());
	if(!pCreator)
		return 0;
	
	return pCreator->createWidget(property);
}

bool PropertyWidgetFactory::destroyWidget(PropertyWidget *pProperty)
{
	if (!pProperty)
		return false;
	
	// Get the creator of this property
	PropertyWidgetCreator *pCreator = getCreator(pProperty->getProperty()->getType());
	if (!pCreator)
		return false;
	
	pCreator->destroyWidget(pProperty);
	return true;
}


/**********************
* Protected functions *
**********************/

void PropertyWidgetFactory::registerCreator(PropertyWidgetCreator *pCreator)
{
	if (pCreator)
		m_creators[pCreator->getType()] = pCreator;
}

void PropertyWidgetFactory::unregisterCreator(PropertyWidgetCreator *pCreator)
{
	if (pCreator)
		m_creators.erase(pCreator->getType());
}

void PropertyWidgetFactory::createStandardWidgetCreators()
{
	static PropertyWidgetCreatorBool boolCreator;
	static PropertyWidgetCreatorCompound compoundCreator;
	static PropertyWidgetCreatorInt intCreator;
	static PropertyWidgetCreatorUInt uintCreator;
	static PropertyWidgetCreatorReal realCreator;
	static PropertyWidgetCreatorString stringCreator;
}
