#ifndef MIDIME_PLUGINNAME_H
#define MIDIME_PLUGINNAME_H

// Includes
#include "global.h"
#include <PluginSystem/Plugin.h>

namespace MidiMe
{
	// Forward declarations
	class SplitterCreator;
	class DuplicatorCreator;

	/** Plugin Description */
	class StandardProcessorsPlugin: public plugin::Plugin
	{
	public:
		// Constructors and destructor
		StandardProcessorsPlugin();
		virtual ~StandardProcessorsPlugin();

		// plugin::Plugin functions
		bool start(const plugin::KeyValueMap &settings = plugin::KeyValueMap());
		bool stop();

	protected:
		// Member variables
		SplitterCreator *m_pSplitterCreator;
		DuplicatorCreator *m_pDuplicatorCreator;
	};
}

CREATEPLUGIN(MidiMe::StandardProcessorsPlugin)

#endif // MIDIME_PLUGINNAME_H
