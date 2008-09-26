// Includes
#include "Property.h"
#include "PropertyCollection.h"
using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

Property::Property(PropertyCollection *pCollection, const string &name)
: m_pCollection(pCollection), m_name(name), m_pListener(0)
{
	assert(m_pCollection && !m_name.empty());

	// Add this property to the collection
	m_pCollection->addProperty(this);
}

Property::~Property()
{
	// Remove this property from the collection
	m_pCollection->removeProperty(this);
}


/******************
* Other functions *
******************/

void Property::fireChanged()
{
	if(m_pListener)
		m_pListener->onPropertyChanged(this);

	if(m_pCollection)
		m_pCollection->fireChanged(this);
}


/**********************
* Protected functions *
**********************/
