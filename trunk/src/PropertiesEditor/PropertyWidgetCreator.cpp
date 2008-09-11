// Includes
#include "PropertyWidgetCreator.h"
#include "PropertyWidgetFactory.h"

using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

PropertyWidgetCreator::PropertyWidgetCreator(const std::string &type)
{
	m_type = type;
	
	PropertyWidgetFactory::getInstance().registerCreator(this);
}

PropertyWidgetCreator::~PropertyWidgetCreator()
{
	PropertyWidgetFactory::getInstance().unregisterCreator(this);
}
