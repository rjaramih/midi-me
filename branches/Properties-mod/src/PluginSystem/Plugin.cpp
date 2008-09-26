// Includes
#include "Plugin.h"
using namespace plugin;


/******************************
* Constructors and destructor *
******************************/

Plugin::Plugin(const string &name)
: m_name(name), m_started(false)
{
}

Plugin::~Plugin()
{
	//stop();
}


/**********************
* Protected functions *
**********************/

void Plugin::removeDependent(const string &pluginName)
{
	NameVector::iterator it;
	for(it = m_dependents.begin(); it != m_dependents.end(); ++it)
		if(*it == pluginName)
		{
			m_dependents.erase(it);
			return;
		}
}
