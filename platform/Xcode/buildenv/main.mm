//
//  main.m
//  midi-me
//
//  Created by Jeroen Dierckx on 22/07/09.
//  Copyright EDM 2009 . All rights reserved.
//

// Includes
#include <PluginSystem/PluginSystem.h>

// TEMP
#include <libMidi-Me/DeviceManager.h>
#include <libMidi-Me/InputDevice.h>
#include <libMidi-Me/MidiOutput.h>
#include <libMidi-Me/Output.h>
#include <libMidi-Me/Chain.h>
using namespace MidiMe;

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

void initPlugins()
{
	plugin::PluginManager *pPluginMgr = plugin::PluginSystem::getInstance().getPluginManager();
	assert(pPluginMgr);
	
	// Set the plugin path
	//pPluginMgr->setSearchPath("build/Debug/");
	
	// Load plugins
	if(!pPluginMgr->start("StandardProcessors"))
	{
		cerr << "Error starting StandardProcessors plugin!" << endl;
		exit(-1);
	}
}

void deinitPlugins()
{
	plugin::PluginManager *pPluginMgr = plugin::PluginSystem::getInstance().getPluginManager();
	assert(pPluginMgr);
	
	// Stop all plugins that are still running
	pPluginMgr->stopAll();
}


#import <Cocoa/Cocoa.h>

int main(int argc, char *argv[])
{
	// Initialize
	initPlugins();

	MidiMe::MidiOutput *pMidiOut = MidiMe::DeviceManager::getInstance().getMidiOutput();

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
	
	unsigned int numPorts = pMidiOut->numPorts();
	cerr << numPorts << " midi-out port(s) found: " << endl;
	
	for(unsigned int i = 0; i < numPorts; ++i)
		cerr << "  * " << pMidiOut->getPortName(i) << endl;
#endif
	
	// Open a virtual midi port (note: not available on windows)
	if(!pMidiOut->openVirtual())
	{
		cerr << "Error opening virtual midi port: " << pMidiOut->getLastError() << endl;
		return -1;
	}

    int result = NSApplicationMain(argc, (const char **) argv);
	
	// Shut down
	deinitPlugins();
	
	return result;
}
