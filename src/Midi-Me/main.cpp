// Includes
#include "global.h"
#include "MainWindow.h"
#include <PluginSystem/PluginSystem.h>
using namespace MidiMe;

#include <QtCore/QSettings>
#include <QtGui/QApplication>
#include <QtGui/QMessageBox>

// TEMP
#include <libMidi-Me/DeviceManager.h>
#include <libMidi-Me/InputDevice.h>
#include <libMidi-Me/MidiOutput.h>

// TEMP Test input device
class DummyDevice: public InputDevice
{
public:
	DummyDevice(): InputDevice("Dummy")
	{
		addOutput(0, false);
		addOutput(1, true);
	}

	~DummyDevice() {}

protected:
	// Device functions
	bool capture()
	{
		static int counter = 0;

		if(counter % 200 == 0)
			sendMinValue(0);
		else if(counter % 100 == 0)
			sendMaxValue(0);

		if(counter % 200 < 100)
		{
			real value = (counter % 200) * 0.01;
			sendValue(1, value);
		}
		else
		{
			real value = (200 - (counter % 200)) * 0.01;
			sendValue(1, value);
		}

		++counter;
		return true;
	}
};

void initPluginSystem(QWidget *pParentWindow)
{
	plugin::PluginManager *pPluginMgr = plugin::PluginSystem::getInstance().getPluginManager();
	assert(pPluginMgr);

	// Set the plugin path
	pPluginMgr->setSearchPath("Plugins/");

	// Get the previously loaded plugins
	QSettings settings;
	if(settings.contains("plugins"))
	{
		QStringList plugins = settings.value("plugins").toStringList();

		for(int i = 0; i < plugins.size(); ++i)
		{
			if(!pPluginMgr->start(plugins.at(i).toStdString()))
			{
				QString message("The '%1' plugin failed to start");
				message.arg(plugins.at(i));
				QMessageBox::warning(pParentWindow, "Midi-Me :: Error", message);
			}
		}
	}
}

void deinitPluginSystem()
{
	plugin::PluginManager *pPluginMgr = plugin::PluginSystem::getInstance().getPluginManager();
	assert(pPluginMgr);

	// Save the loaded plugins
	QSettings settings;
	QStringList plugins;

	std::set<string> names =  pPluginMgr->getStartedPlugins();
	std::set<string>::iterator it;
	for(it = names.begin(); it != names.end(); ++it)
		plugins << (*it).c_str();

	settings.setValue("plugins", plugins);

	// Stop all plugins that are still running
	pPluginMgr->stopAll();
}


/*! The application's main function */
int main(int argc, char *argv[])
{
	// Setup the application
	QApplication app(argc, argv);
	app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
	app.setOrganizationName("JeDiTech");
	app.setApplicationName("MidiMe");

	// create and show main window
	MainWindow *pWindow = new MainWindow();
	DeviceManager::getInstance().setWindowHandle((size_t) pWindow->winId());
	pWindow->show();

	// Setup the plugin system
	initPluginSystem(pWindow);

#if 1
	// TEMP: Register dummy device
	DummyDevice dummyDevice;

	cerr << endl;

	// TEMP: Test Midi-Me
	DeviceManager &devMgr = DeviceManager::getInstance();
	cerr << "DeviceManager: " << devMgr.numInputDevices() << " input device(s) found: " << endl;

	const InputDeviceMap &devices = devMgr.getInputDevices();
	InputDeviceMap::const_iterator it;
	for(it = devices.begin(); it != devices.end(); ++it)
	{
		InputDevice *pDevice = it->second;
		cerr << "  * " << pDevice->getName() << endl;
		cerr << "    -> ";
		cerr << pDevice->numOutputs() << " output(s)" << endl;
	}
	
	cerr << endl;

	MidiOutput *pMidiOut = devMgr.getMidiOutput();
	unsigned int numPorts = pMidiOut->numPorts();
	cerr << numPorts << " midi-out port(s) found: " << endl;

	for(unsigned int i = 0; i < numPorts; ++i)
		cerr << "  * " << pMidiOut->getPortName(i) << endl;
#endif

	// Start the application's main loop
	int result = app.exec();

	// Make sure everyting is cleaned up before the application ends
	delete pWindow;
	deinitPluginSystem();

	return result;
}
