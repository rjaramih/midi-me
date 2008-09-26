#ifndef MIDIME_PLUGINNAME_H
#define MIDIME_PLUGINNAME_H

// Includes
#include "global.h"
#include <PluginSystem/Plugin.h>

namespace MidiMe
{
	// Forward declarations

	/** Plugin Description */
	class PluginName: public plugin::Plugin
	{
	protected:
		// Member variables

	public:
		// Constructors and destructor
		PluginName();
		virtual ~PluginName();

		// plugin::Plugin functions
		bool start();
		bool stop();

		// Other functions
	};
}

CREATEPLUGIN(MidiMe::PluginName)

#endif // MIDIME_PLUGINNAME_H
