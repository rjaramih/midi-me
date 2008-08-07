#ifndef NVE_PLUGINNAME_H
#define NVE_PLUGINNAME_H

// Includes
#include "global.h"
#include <PluginSystem/Plugin.h>

namespace NVE
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

CREATEPLUGIN(NVE::PluginName)

#endif // NVE_PLUGINNAME_H
