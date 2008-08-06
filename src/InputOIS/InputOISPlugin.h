#ifndef MIDIME_INPUTOISPLUGIN_H
#define MIDIME_INPUTOISPLUGIN_H

// Includes
#include "global.h"
#include <PluginSystem/Plugin.h>
#include <list>

// Forward declarations
namespace OIS { class InputManager; }

namespace MidiMe
{
	// Forward declarations
	class JoyStick;
	typedef std::vector<JoyStick *> JoyStickVector;

	/** Plugin Description */
	class InputOISPlugin: public plugin::Plugin
	{
	public:
		// Constructors and destructor
		InputOISPlugin();
		virtual ~InputOISPlugin();

		// plugin::Plugin functions
		bool start(const plugin::KeyValueMap &settings);
		bool stop();

	protected:
		// Other functions
		bool initOIS();
		bool destroyOIS();

		// Member variables
		OIS::InputManager *m_pInputMgr;
		JoyStickVector m_joySticks;
	};
}

CREATEPLUGIN(MidiMe::InputOISPlugin)

#endif // MIDIME_INPUTOISPLUGIN_H
