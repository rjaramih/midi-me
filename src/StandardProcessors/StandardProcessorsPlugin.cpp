// Includes
#include "StandardProcessorsPlugin.h"
#include "Splitter.h"
#include "Duplicator.h"
using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

StandardProcessorsPlugin::StandardProcessorsPlugin()
: plugin::Plugin("StandardProcessors")
, m_pSplitterCreator(0), m_pDuplicatorCreator(0)
{
}

StandardProcessorsPlugin::~StandardProcessorsPlugin()
{
}


/***************************
* plugin::Plugin functions *
***************************/

bool StandardProcessorsPlugin::start(const plugin::KeyValueMap &settings)
{
	m_pSplitterCreator = new SplitterCreator();
	m_pDuplicatorCreator = new DuplicatorCreator();

	m_settings = settings;
	m_started = true;
	return true;
}

bool StandardProcessorsPlugin::stop()
{
	delete m_pDuplicatorCreator; m_pDuplicatorCreator = 0;
	delete m_pSplitterCreator; m_pSplitterCreator = 0;

	m_started = false;
	return true;
}


/******************
* Other functions *
******************/


/**********************
* Protected functions *
**********************/
