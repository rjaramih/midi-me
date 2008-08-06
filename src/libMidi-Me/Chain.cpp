// Includes
#include "Chain.h"
#include "Serializer.h"
using namespace MidiMe;

#include <RtMidi/RtMidi.h>


/******************************
* Constructors and destructor *
******************************/

Chain::Chain()
: m_started(false), m_dirty(false)
{
}

Chain::~Chain()
{
}


/******************
* Other functions *
******************/

bool Chain::loadSettings(const string &filename)
{
	Serializer loader;
	if(!loader.load(this, filename))
	{
		setLastError("Error loading settings from '" + filename + "': " + loader.getLastError());
		return false;
	}

	m_currentFile = filename;
	m_dirty = false;

	return true;
}

/** Save this chain to the currently opened file */
bool Chain::saveSettings()
{
	if(m_currentFile.empty())
	{
		setLastError("No currently opened file");
		return false;
	}

	return saveSettings(m_currentFile);
}

bool Chain::saveSettings(const string &filename)
{
	Serializer saver;
	if(!saver.save(this, filename))
	{
		setLastError("Error saving settings to '" + filename + "': " + saver.getLastError());
		return false;
	}

	m_currentFile = filename;
	m_dirty = false;

	return true;
}


/**********************
* Protected functions *
**********************/
