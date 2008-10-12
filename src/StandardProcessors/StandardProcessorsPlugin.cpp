// Includes
#include "StandardProcessorsPlugin.h"
#include "Inverter.h"
#include "Splitter.h"
#include "Duplicator.h"
#include "Delay.h"
using namespace MidiMe;


/******************************
* Constructors and destructor *
******************************/

StandardProcessorsPlugin::StandardProcessorsPlugin()
: plugin::Plugin("StandardProcessors")
, m_pInverterCreator(0), m_pSplitterCreator(0), m_pDuplicatorCreator(0), m_pDelayCreator(0)
{
	setDescription("This plugin provides some standard processor items, like an inverter, splitter, delay, ...");
}

StandardProcessorsPlugin::~StandardProcessorsPlugin()
{
}


/***************************
* plugin::Plugin functions *
***************************/

bool StandardProcessorsPlugin::start(const plugin::KeyValueMap &settings)
{
	m_pInverterCreator = new InverterCreator();
	m_pSplitterCreator = new SplitterCreator();
	m_pDuplicatorCreator = new DuplicatorCreator();
	m_pDelayCreator = new DelayCreator();

	m_settings = settings;
	m_started = true;
	return true;
}

bool StandardProcessorsPlugin::stop()
{
	delete m_pDelayCreator; m_pDelayCreator = 0;
	delete m_pDuplicatorCreator; m_pDuplicatorCreator = 0;
	delete m_pSplitterCreator; m_pSplitterCreator = 0;
	delete m_pInverterCreator; m_pInverterCreator = 0;

	m_started = false;
	return true;
}


/******************
* Other functions *
******************/


/**********************
* Protected functions *
**********************/
