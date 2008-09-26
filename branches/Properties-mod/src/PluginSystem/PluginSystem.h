#ifndef PLUGIN_PLUGINSYSTEM_H
#define PLUGIN_PLUGINSYSTEM_H

// Includes
#include "global.h"
#include "DllManager.h"
#include "PluginManager.h"

namespace plugin
{
	/**
		This singleton class contains the PluginSystem and the PluginManager
		of the plugin system. Using the singleton mechanism, the managers are
		always available to the user.
	*/
	class PLUGINSYSTEM_API PluginSystem
	{
	private:
		// Member variables
		DllManager m_dllManager;
		PluginManager m_pluginManager;

		// Private constructors and destructor
		PluginSystem();
		PluginSystem(const PluginSystem &source); //!< Copy constructor, intentionally not implemented
		virtual ~PluginSystem();

		//! Private assignment operator, intentionally not implemented
		PluginSystem &operator =(const PluginSystem &source);

	public:
		// Singleton function
		static PluginSystem &getInstance();

		// Get functions
		DllManager *getDllManager() { return &m_dllManager; }
		PluginManager *getPluginManager() { return &m_pluginManager; }
	};


	// Some convenience macros
	#define gpDllManager PluginSystem::getInstance().getDllManager()
	#define gpPluginManager PluginSystem::getInstance().getPluginManager()
}

#endif // PLUGIN_PLUGINSYSTEM_H
