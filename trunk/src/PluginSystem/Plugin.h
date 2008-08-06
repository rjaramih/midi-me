#ifndef PLUGIN_PLUGIN_H
#define PLUGIN_PLUGIN_H

// Includes
#include "global.h"
#include <vector>
#include <map>

namespace plugin
{
	// Forward declarations

	// Typedefs
	typedef std::vector<string> NameVector;
	typedef std::map<string, string> KeyValueMap;


	/**
		A plugin gets automatically created by a dynamic library.
		A plugin contains functions to start and stop, so by deriving from this class
		and implementing the start and stop functions, plugins can be used to extend
		applications by 3rd-party implementations.
		A plugin can contain a list of dependencies, that will be loaded automatically
		before this one.
	*/
	class PLUGINSYSTEM_API Plugin
	{
	protected:
		// Member variables
		string m_name; //!< The name of this plugin. @todo We should derive this from the file name and pre- and suffix
		string m_description; //!< A short description for this plugin, if provided.
		KeyValueMap m_settings; //!< The settings provided when starting the plugin
		bool m_started;
		NameVector m_dependencies; //!< Plugins that are required for this one (filled in by the plugin itself)
		NameVector m_dependents; //!< Plugins that depend on this one (filled in by the PluginManager)

	public:
		// Constructors and destructor
		Plugin(const string &name);
		virtual ~Plugin();

		// Get functions
		const string &getName() const { return m_name; }
		const string &getDescription() const { return m_description; }
		const KeyValueMap &getSettings() const { return m_settings; }

		// Dependency functions
		unsigned int numDependencies() const { return m_dependencies.size(); }
		const string &getDependency(unsigned int i) const { return m_dependencies[i]; }
		const NameVector &getDependencyVector() const { return m_dependencies; }

		// Dependents functions
		unsigned int numDependents() const { return m_dependents.size(); }
		const string &getDependent(unsigned int i) const { return m_dependents[i]; }
		const NameVector &getDependentVector() const { return m_dependents; }

		// Other functions
		//! @note Implementations should set m_started at true when finished, and store the settings in m_settings
		//virtual bool start(const KeyValueMap &settings = KeyValueMap()) { m_settings = settings; m_started = true; return true; }
		virtual bool start(const KeyValueMap &settings = KeyValueMap()) = 0;
		//! @note Implementations should set m_started at false when finished
		//virtual bool stop() { m_started = false; return true; }
		virtual bool stop() = 0;
		virtual bool restart() { return stop() && start(m_settings); }
		bool isStarted() const { return m_started; }

		// Locking functions (called when the plugin is locked)
		virtual void lock() {};
		virtual void unlock() {};

	protected:
		// Protected functions
		void setDescription(const string &description) { m_description = description; }
		void addDependency(const string &pluginName) { m_dependencies.push_back(pluginName); }
		void addDependent(const string &pluginName) { m_dependents.push_back(pluginName); }
		void removeDependent(const string &pluginName);

	// Friends
	friend class PluginManager;
	};
}


// This macro can be used to create a plugin library
//! @warning If other files have to include the plugin's header, you have to put this in the cpp file!
#define CREATEPLUGIN(name) \
	PLUGIN_API plugin::Plugin *createPlugin() \
	{ \
		return new name(); \
	} \
	PLUGIN_API void destroyPlugin(plugin::Plugin *pPlugin) \
	{ \
		delete pPlugin; \
	}


#endif // PLUGIN_PLUGIN_H
