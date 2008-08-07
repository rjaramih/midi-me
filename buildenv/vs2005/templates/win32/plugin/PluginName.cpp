// Includes
#include "PluginName.h"
using namespace NVE;


/******************************
* Constructors and destructor *
******************************/

PluginName::PluginName()
: plugin::Plugin("PluginName")
{
}

PluginName::~PluginName()
{
}


/***************************
* plugin::Plugin functions *
***************************/

bool PluginName::start()
{
	m_started = true;
	return true;
}

bool PluginName::stop()
{
	m_started = false;
	return true;
}


/******************
* Other functions *
******************/


/**********************
* Protected functions *
**********************/
