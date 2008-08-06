// Includes
#include "PluginManager.h"
#include "PluginSystem.h"
#include "Plugin.h"
#include "DynamicLibrary.h"
#include "StringUtil.h"
using namespace plugin;
using namespace NVE;


// Typedefs
typedef Plugin *(*CreateFunction)(void); //!< A function pointer to create the plugin
typedef void (*DestroyFunction)(Plugin *); //!< A function pointer to destroy the plugin


/******************************
* Constructors and destructor *
******************************/

PluginManager::PluginManager() : m_bClearing(false)
{
}

/*! The destructor unlocks and stops all remaining plugins. */
PluginManager::~PluginManager()
{
	// Unlock all plugins (so they can be stopped)
	unlockAll();

	// Stop the remaining plugins
	stopAll();
}


/*********************
* Filename functions *
*********************/

/*! Set the search path for plugins
	@param path The search path
*/
void PluginManager::setSearchPath(const string &path)
{
	m_path = path;

	// Clean up the path
	StringUtil::cleanPath(m_path);
	cerr << "[PluginManager] Setting the search path to " << m_path << endl;

	//! @todo Add support for other platforms
#if defined(_WIN32_WCE) || defined(WIN32)
	//::SetDllDirectoryA(m_path.c_str());
#endif // _WIN32_WCE || WIN32
}


/*************************
* Start / stop functions *
*************************/

/*! Checks if a plugin is started.
	@param name The name of the plugin you want to check
	@return True if the plugin is started, false if it isn't
*/
bool PluginManager::isStarted(const string &name) const
{
	PluginMap::const_iterator it = m_plugins.find(name);
	return it != m_plugins.end();
}

/*! Starts a plugin, after its dependencies.
	@return True if successfull, false if failed.

	@param name
		The name of the plugin, not the filename of the library! The filename
		is automatically generated from the name. \see getLibraryName
	@param settings
		A key-value map that you can optionally provide to the plugin that is started
*/
bool PluginManager::start(const string &name, const KeyValueMap &settings)
{
	// Check if the plugin is already started
	if(isStarted(name)) return true;

	// Load the plugin library
	string libname = getLibraryName(name);
	DllManager *pDllMgr = PluginSystem::getInstance().getDllManager();
	DynamicLibrary *pLib = pDllMgr->loadLibrary(libname);
	if(!pLib)
	{
		cerr << "[PluginManager] Error starting plugin '" << name << "': ";
		DynamicLibrary::correctFilename(libname);
		cerr << "Error loading dynamic library " << libname << endl;
		return false;
	}

	// Create the plugin
	CreateFunction createFunc = (CreateFunction) pLib->getSymbol("createPlugin");
	DestroyFunction destroyFunc = (DestroyFunction) pLib->getSymbol("destroyPlugin");
	if(!createFunc || !destroyFunc)
	{
		cerr << "[PluginManager] Error starting plugin '" << name << "': ";
		cerr << "Create and/or destroy function not exported" << endl;
		return false;
	}

	Plugin *pPlugin = createFunc();
	assert(pPlugin);

	// Start its dependencies and add this as dependent
	// Note that they are started without settings, they have to be started explicitly when settings are needed
	for(unsigned int i = 0; i < pPlugin->numDependencies(); ++i)
	{
		const string &dep = pPlugin->getDependency(i);
		start(dep);

		if(!isStarted(dep))
		{
			cerr << "[PluginManager] Error starting plugin '" << name << "': ";
			cerr << "A dependency plugin failed to load" << endl;

			destroyFunc(pPlugin);
			return false;
		}

		// Add to dependent list
		Plugin *pDepPlugin = getPlugin(dep);
		assert(pDepPlugin);
		pDepPlugin->addDependent(name);
	}

	// Start the plugin
	if(!pPlugin->start(settings))
	{
		cerr << "[PluginManager] Error starting plugin '" << name << "': ";
		cerr << "Start function returned false" << endl;

		destroyFunc(pPlugin);
		return false;
	}

	// Add the plugin to the map
	m_plugins[name] = pPlugin;
	cerr << "[PluginManager] Successfully started plugin '" << name << "'" << endl;
	return true;
}

/*! Stops a plugin, after its dependents.

	@param name The name of the plugin to be stopped
	@param stopDependents Stop running dependents of the plugin first? If false, the plugin isn't stopped if there are running dependents
	@return True if successfull, false if failed.

	@note We use the name parameter by value because otherwise the reference could be invalid after destroying the plugin

	@todo
	- Throw an exception when the plugin (or one of its dependents) is locked. The user has to unlock it first
	- Throw exception when there are running dependents and stopDependents is false
*/
bool PluginManager::stop(const string name, bool stopDependents)
{
	unsigned int i;

	// Check if the plugin is started
	if(!isStarted(name)) return true;

	// Check if the plugin is locked
	if(isLocked(name))
	{
		cerr << "[PluginManager] Error stopping plugin '" << name << "': ";
		cerr << "The plugin is locked" << endl;
		return false;
	}

	// Get the plugin
	Plugin *pPlugin = getPlugin(name);
	assert(pPlugin);

	// Stop its dependents
	unsigned int numDependents = pPlugin->numDependents();
	if(numDependents > 0 && !stopDependents)
	{
		cerr << "[PluginManager] Error stopping plugin '" << name << "': ";
		cerr << "There are still dependent plugins running" << endl;
		return false;
	}

	for(i = 0; i < numDependents; ++i)
	{
		const string &depName = pPlugin->getDependent(i);
		if(!stop(depName, stopDependents))
		{
			cerr << "[PluginManager] Error stopping plugin '" << name << "': ";
			cerr << "A dependent plugin failed to stop" << endl;
			return false;
		}
	}

	// Stop the plugin
	pPlugin->stop();

	// Remove from the dependencies dependent list
	if(!m_bClearing)
	{
		for(i = 0; i < pPlugin->numDependencies(); ++i)
		{
			const string &depName = pPlugin->getDependency(i);

			Plugin *pDepPlugin = getPlugin(depName);
			assert(pDepPlugin);
			pDepPlugin->removeDependent(name);
		}
	}

	// Get the plugin library
	string libname = getLibraryName(name);
	DllManager *pDllMgr = PluginSystem::getInstance().getDllManager();
	DynamicLibrary *pLib = pDllMgr->loadLibrary(libname);
	if(pLib)
	{
		// Remove the plugin
		DestroyFunction destroyFunc = (DestroyFunction) pLib->getSymbol("destroyPlugin");
		if(destroyFunc)
			destroyFunc(pPlugin);
		else
			delete pPlugin;
	}
	else
		delete pPlugin;

	m_plugins.erase(name);
	cerr << "[PluginManager] Successfully stopped plugin '" << name << "'" << endl;
	return true;
}

/*! Restarts a plugin, and optionally its dependents.
	@param name The name of the plugin you want to restart
	@param restartDependents Restart running dependents of the plugin first? If false, the plugin isn't restarted if there are running dependents
	@return True if successfull, false if failed.

	@todo Add a restart function to the Plugin class, because the settings have to be set again
*/
bool PluginManager::restart(const string &name, bool restartDependents)
{
	// If the plugin isn't started yet, it doesn't have any dependents
	if(!isStarted(name))
		return start(name);

	// Check if the plugin is locked
	if(isLocked(name))
		return false;

	// Get the plugin
	Plugin *pPlugin = getPlugin(name);
	assert(pPlugin);

	// Check if the plugin has running dependents
	unsigned int numDependents = pPlugin->numDependents();
	if(!restartDependents && numDependents > 0)
		return false;

	// Take track of the dependents (make a copy of the list)
	NameVector dependents = pPlugin->getDependentVector();

	// Stop the plugin (along with its dependents)
	if(!stop(name, true))
		return false;

	// Restart the plugin
	if(!start(name))
		return false;

	// Restart its dependents
	NameVector::iterator it;
	for(it = dependents.begin(); it != dependents.end(); ++it)
		if(!start(*it))
			return false;

	return true;
}

/*! Stop all plugins, and their dependents (locked plugins aren't stopped).
	@return True if successfull, false if failed.
*/
bool PluginManager::stopAll()
{
	bool success = true;
	m_bClearing = true;

	while(!allPluginsStopped())
	{
		const string &name = m_plugins.begin()->first;
		if(isLocked(name))
			continue;

		if(!stop(name, true))
			success = false;
	}

	m_bClearing = false;
	return success;
}

/*! Restart all plugins, and their dependents.
	@return True if successfull, false if failed.
*/
bool PluginManager::restartAll()
{
	// Take track of the plugins that are started
	std::vector<string> plugins;
	PluginMap::iterator it;
	for(it = m_plugins.begin(); it != m_plugins.end(); ++it)
		plugins.push_back(it->first);

	// Restart the plugins
	bool success = true;
	std::vector<string>::iterator it2;
	for(it2 = plugins.begin(); it2 != plugins.end(); ++it2)
		if(!restart(*it2, true))
			success = false;

	return success;
}

PluginManager::NameSet PluginManager::getStartedPlugins() const
{
	NameSet plugins;

	PluginMap::const_iterator it;
	for(it = m_plugins.begin(); it != m_plugins.end(); ++it)
		plugins.insert(it->first);

	return plugins;
}


/*******************
* Plugin functions *
*******************/

/*! Get a loaded plugin
	@param name The name of the plugin you want to get
	@return A pointer to the loaded plugin. 0 if the plugin isn't loaded
*/
const Plugin *PluginManager::getPlugin(const string &name) const
{
	PluginMap::const_iterator it = m_plugins.find(name);
	if(it == m_plugins.end())
		return 0;

	return it->second;
}

/*! Get a loaded plugin
	@param name The name of the plugin you want to get
	@return A pointer to the loaded plugin. 0 if the plugin isn't loaded
*/
Plugin *PluginManager::getPlugin(const string &name)
{
	PluginMap::iterator it = m_plugins.find(name);
	if(it == m_plugins.end())
		return 0;

	return it->second;
}

/*! Check if a plugin has dependencies
	@param pluginName The name of the plugin you want to check
	@return True if the plugin has dependencies, false otherwise
*/
bool PluginManager::hasDependencies(const string &pluginName) const
{
	// Check if the plugin is started
	if(!isStarted(pluginName)) return false;

	// Get the plugin
	const Plugin *pPlugin = getPlugin(pluginName);
	assert(pPlugin);

	return !pPlugin->getDependencyVector().empty();
}

/*! Check if a plugin has dependents
	@param pluginName The name of the plugin you want to check
	@return True if other plugins depend on this one, false otherwise
*/
bool PluginManager::hasDependents(const string &pluginName) const
{
	// Check if the plugin is started
	if(!isStarted(pluginName)) return false;

	// Get the plugin
	const Plugin *pPlugin = getPlugin(pluginName);
	assert(pPlugin);

	return !pPlugin->getDependentVector().empty();
}


/********************
* Locking functions *
********************/

/*! Lock a plugin (so it won't be stopped or restarted before you unlock it)
	@param name The name of the plugin you want to lock
	@todo Start the plugin if it isn't yet?
*/
void PluginManager::lock(const string &name)
{
	Plugin *pPlugin = getPlugin(name);
	if(pPlugin)
		pPlugin->lock();

	m_lockedPlugins.insert(name);
}

/*! Unlocks a plugin, so it can be stopped or restarted again
	@param name The name of the plugin you want to unlock
*/
void PluginManager::unlock(const string &name)
{
	Plugin *pPlugin = getPlugin(name);
	if(pPlugin)
		pPlugin->unlock();

	m_lockedPlugins.erase(name);
}

/*! Checks if a plugin is locked
	@param name The name of the plugin you want to check
	@return True if the plugin is locked, false if it isn't
*/
bool PluginManager::isLocked(const string &name) const
{
	return m_lockedPlugins.find(name) != m_lockedPlugins.end();
}

/*! Unlock all loaded plugins */
void PluginManager::unlockAll()
{
	NameSet::iterator it;
	for(it = m_lockedPlugins.begin(); it != m_lockedPlugins.end(); ++it)
	{
		Plugin *pPlugin = getPlugin(*it);
		if(pPlugin)
			pPlugin->unlock();
	}

	m_lockedPlugins.clear();
}


/******************
* Other functions *
******************/

/*!
	Generate the plugin's dynamic library name from its regular name.
	
	The plugin's library name is determined by his name, along with
	the path, prefix and suffix you can set in this manager.
	
	The library name on his turn, will be converted to a filename by
	the DynamicLibrary class (as that is platform specific).

	The library name is constructed as follows: "path + prefix + name + suffix".
*/
string PluginManager::getLibraryName(const string &pluginName) const
{
	return m_path + m_prefix + pluginName + m_suffix;
}


/**********************
* Protected functions *
**********************/

/*! Checks if all the (not locked) plugins are stopped.
	@return True if all (non-locked) plugins are stopped, false otherwise
*/
bool PluginManager::allPluginsStopped() const
{
	if(m_plugins.empty())
		return true;

	// Check if the plugins that are loaded are locked
	PluginMap::const_iterator it;
	for(it = m_plugins.begin(); it != m_plugins.end(); ++it)
		if(!isLocked(it->first))
			return false;

	return true;
}
