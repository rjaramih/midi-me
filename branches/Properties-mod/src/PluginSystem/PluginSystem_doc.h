/* This file only contains comments, to provide documentation
generated by Doxygen. No need to include this file in the distribution */

/**

\page plugin_page Plugin System

\section intro_sec Introduction
This library is a plugin system, which contains of all necesarry parts
for working with dynamic libraries and plugins.

The plugin system is a singleton which gives you a single point of access
to the dll and plugin managers.
The following is an example of how you can start a plugin:
\code
#include <PluginSystem/PluginSystem.h>
using namespace plugin;

PluginSystem::getInstance().getPluginManager()->start("MyPlugin");
\endcode

@note We also provide macros to ease the use of the managers (see plugin::PluginSystem).
The previous code can also be written as follows:
\code
#include <PluginSystem/PluginSystem.h>
using namespace plugin;

gpPluginManager->start("MyPlugin");
\endcode

\section dlls_sec Dynamic libraries
The plugin system contains classes which you can use to load dynamic libraries
in a platform-independent way and resolve symbols from them.
The dll manager keeps track of the loaded libraries, and makes sure you don't load
the same library twice. \see plugin::DllManager

\section plugins_sec Plugins
The system also contains classes to easily work with "plugins".
Plugins are dynamic libraries that contain a special exported function
that creates an instance of a Plugin class. A Plugin has functions to start
and stop itself, and can contain a list of dependencies (other plugins that
are needed to be able to start this one).
The plugin manager is used to start and stop plugins. The dependencies will
automatically be started first if necesarry. \see plugin::PluginManager

There is also the possibility to lock certain plugins, so they won't be stopped
or restarted until they are unlocked again.

\subsection createplugins_sec Creating plugins
To create a plugin, you have to derive a class from plugin::Plugin, and implement the
start and stop functions. You can also implement the lock and unlock functions
to do something special when the plugin is locked / unlocked. In your plugin class,
you can give a list of dependency plugins that are needed for this one to work.
You can also set the description for this plugin with the setDescription function.

The plugin dll also has to export the function "createPlugin" (in C-style),
which creates a new instance of the plugin you've created.
You can use the provided CREATEPLUGIN macro to do this automatically.
Just put the macro under the class you've created, so the plugin can be loaded.

@note There can only be one plugin class in a dynamic library

\subsubsection example_sec Example
This is an example of the header of a plugin class:
\code
#ifndef MYPLUGIN_H
#define MYPLUGIN_H

// Includes
#include <PluginSystem/PluginSystem.h>
#include <PluginSystem/Plugin.h>

class MyPlugin: public plugin::Plugin
{
public:
	// Constructor and destructor
	MyPlugin(): plugin::Plugin("MyPlugin") {}
	virtual ~MyPlugin() {}

	// Overloaded functions
	bool start() { cout << "The plugin starts!" << endl; m_started = true; return true; }
	bool stop() { cout << "The plugin stops!" << endl; m_started = false; return true; }
};

// A function to dynamically load the plugin
CREATEPLUGIN(MyPlugin)

#endif // MYPLUGIN_H
\endcode

*/