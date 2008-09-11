// Includes
#include "StandardProperties.h"
#include "StringUtil.h"
using namespace MidiMe;

// Static variables
string CompoundProperty::type("compound");
string BoolProperty::type("bool");
string IntProperty::type("int");
string RealProperty::type("real");
string StringProperty::type("string");


/*******************
* CompoundProperty *
*******************/

CompoundProperty::CompoundProperty(const string &name)
: Property(name)
{
}

CompoundProperty::~CompoundProperty()
{
	clearProperties();
}

string CompoundProperty::toString() const
{
	string result("(");

	PropertyMap::const_iterator it;
	for(it = m_properties.begin(); it != m_properties.end(); ++it)
	{
		if(it != m_properties.begin())
			result += ", ";

		result += it->second->toString();
	}

	result += ")";
	return result;
}

void CompoundProperty::fromString(const string &value)
{
	//! @warning Compound properties can't be constructed from a string!
}

void CompoundProperty::fireChanged()
{
	Property::fireChanged();

	PropertyMap::iterator it;
	for(it = m_properties.begin(); it != m_properties.end(); ++it)
		it->second->fireChanged();
}

void CompoundProperty::onPropertyChanged(Property *pProperty)
{
	Property::fireChanged();
}

bool CompoundProperty::addProperty(Property *pProperty)
{
	if(!pProperty) return false;

	const string &name = pProperty->getName();
	if(m_properties.find(name) != m_properties.end())
		return false;

	m_properties[name] = pProperty;
	pProperty->setListener(this);
	return true;
}

bool CompoundProperty::removeProperty(Property *pProperty)
{
	if(!pProperty) return true;

	PropertyMap::iterator it = m_properties.find(pProperty->getName());
	if(it == m_properties.end()) return false;

	it->second->clearListener();
	m_properties.erase(it);
	return true;
}

void CompoundProperty::clearProperties()
{
	PropertyMap::iterator it;
	for(it = m_properties.begin(); it != m_properties.end(); ++it)
		it->second->clearListener();

	m_properties.clear();
}

Property *CompoundProperty::getProperty(const string &name) const
{
	PropertyMap::const_iterator it = m_properties.find(name);
	return (it == m_properties.end()) ? 0 : it->second;
}


/***************
* BoolProperty *
***************/

string BoolProperty::toString() const
{
	return StringUtil::toString(getValue());
}

void BoolProperty::fromString(const string &value)
{
	setValue(StringUtil::toBool(value));
}


/**************
* IntProperty *
**************/

string IntProperty::toString() const
{
	return StringUtil::toString(getValue());
}

void IntProperty::fromString(const string &value)
{
	setValue(StringUtil::toInt(value));
}


/***************
* RealProperty *
***************/

string RealProperty::toString() const
{
	return StringUtil::toString(getValue());
}

void RealProperty::fromString(const string &value)
{
	setValue(StringUtil::toFloat(value));
}


/****************
* StringProperty *
****************/

string StringProperty::toString() const
{
	return getValue();
}

void StringProperty::fromString(const string &value)
{
	setValue(value);
}
