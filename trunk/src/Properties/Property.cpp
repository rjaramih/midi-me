// Includes
#include "Property.h"
#include "PropertyCollection.h"
using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

Property::Property(const string &name)
: m_name(name), m_pCollection(0), m_pListener(0)
{
}

Property::~Property()
{
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
