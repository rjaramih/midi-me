// Includes
#include "PluginSystem.h"
using namespace plugin;


/*!
	Get the instance of this singleton class.
	You need to use this function to access the class,
	as the constructor is private.
*/
PluginSystem &PluginSystem::getInstance()
{
	static PluginSystem instance;
	return instance;
}


/******************************
* Constructors and destructor *
******************************/

PluginSystem::PluginSystem()
{
}

PluginSystem::~PluginSystem()
{
}
