#ifndef PLUGIN_PLUGINMANAGER_H
#define PLUGIN_PLUGINMANAGER_H

// Includes
#include "global.h"
#include <map>
#include <set>

namespace plugin
{
	// Forward declarations
	class Plugin;

	/** A key-value pair map that you can provide to a starting plugin */
	typedef std::map<string, string> KeyValueMap;

	/**
		This class is used to manage plugins. Plugins are created by special dynamic libraries,
		and used to extend an application.
		The manager can start plugins, and makes sure dependent plugins are started first.
		
		The plugin manager contains a search path and a pre- and postfix to map plugin names
		to dynamic library names. So you can have a plugin called "Thingy", and with a prefix
		"plugin", the library name will be "pluginThingy" (which will be corrected to
		"pluginThingy.dll" on windows and "libpluginThingy.so" on linux).

		The plugin manager also contains a locking mechanism. Plugins can be locked,
		and will not be automatically stopped or restarted. In that way, plugins can
		be garuanteed to stay started as long as you want.

		@todo
			- Check for circular dependencies
			- If there are no dependents left, plugins can be stopped if they aren't explicitly loaded
			  (so not as a dependency)
			- Keep a set of explicitly loaded plugins (to keep track of which dependencies to unload)
			- Add a search path to the DllManager, and use that here?
	*/
	class PLUGINSYSTEM_API PluginManager
	{
	protected:
		// Typedefs
		typedef std::map<string, Plugin *> PluginMap;
		typedef std::set<string> NameSet;

		// Member variables
		string m_path, m_prefix, m_suffix;
		PluginMap m_plugins; //!< A map containing the plugins, mapped with their names
		NameSet m_lockedPlugins; //!< A set containing the plugins that are locked (they will not be deleted or restarted automatically)
		bool m_bClearing;

	public:
		// Constructors and destructor
		PluginManager();
		virtual ~PluginManager();

		// Filename functions
		const string &getSearchPath() const { return m_path; }
		void setSearchPath(const string &path);
		const string &getPrefix() const { return m_prefix; }
		void setPrefix(const string &prefix) { m_prefix = prefix; }
		const string &getSuffix() const { return m_suffix; }
		void setSuffix(const string &suffix) { m_suffix = suffix; }

		// Start / stop functions
		bool isStarted(const string &name) const;
		bool start(const string &name, const KeyValueMap &settings = KeyValueMap());
		bool stop(const string name, bool stopDependents = false);
		bool restart(const string &name, bool restartDependents = false);
		bool stopAll();
		bool restartAll();
		NameSet getStartedPlugins() const;

		// Plugin functions
		const Plugin *getPlugin(const string &name) const;
		Plugin *getPlugin(const string &name);
		bool hasDependencies(const string &pluginName) const;
		bool hasDependents(const string &pluginName) const;

		// Locking functions
		void lock(const string &name);
		void unlock(const string &name);
		bool isLocked(const string &name) const;
		void unlockAll();

		// Other functions
		string getLibraryName(const string &pluginName) const;

	private:
		// Private functions
		bool allPluginsStopped() const;
	};
}

#endif // PLUGIN_PLUGINMANAGER_H
