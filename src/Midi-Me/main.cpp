// Includes
#include "global.h"
#include "MainWindow.h"
using namespace MidiMe;

#include <QtGui/QApplication>

// TEMP
#include <libMidi-Me/DeviceManager.h>
#include <libMidi-Me/InputDevice.h>
#include <libMidi-Me/MidiOutput.h>
#include <PluginSystem/PluginSystem.h>

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


/*! The application's main function */
int main(int argc, char *argv[])
{
	// Setup the plugin system
	plugin::PluginManager *pPluginMgr = plugin::PluginSystem::getInstance().getPluginManager();
	pPluginMgr->setSearchPath("Plugins/");

	// Setup the application
	QApplication app(argc, argv);
	app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
	app.setOrganizationName("JeDiTech");
	app.setApplicationName("MidiMe");

	// create and show main window
	MainWindow *pWindow = new MainWindow();
	DeviceManager::getInstance().setWindowHandle((size_t) pWindow->winId());
	pWindow->show();

#if 1
	// TEMP: Start standard processors plugin
	if(!pPluginMgr->start("StandardProcessors"))
	{
		cerr << "Error starting standard processors plugin!" << endl;
		return -1;
	}

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
	pPluginMgr->stopAll();

	return result;
}
