// Includes
#include "MainWindow.h"
#include <Converter/ConverterManager.h>
#include <Converter/AxisConverter.h>
using namespace MidiMe;

#include <QtCore/QSettings>
#include <QtGui/QMessageBox>
#include <QtGui/QInputDialog>
#include <QtCore/QTimer>


//! The (hardcoded) maximum number of recently opened files
static const unsigned int s_numRecentFiles = 5;


/******************************
* Constructors and destructor *
******************************/

MainWindow::MainWindow()
: m_pConverter(0), m_timerId(0)
{
	createWidgets();
	loadSettings();

	// Create the converter
	m_pConverter = new ConverterManager();

	// TEMP: hardcoded settings
	AxisConverter *pAxis = m_pConverter->addAxisConverter(2);
	AxisConverter::Slice slice;

	// Left pedal to controller 16
	slice.minValue = -255;
	slice.maxValue = OIS::JoyStick::MAX_AXIS;
	slice.controller = 16;
	pAxis->addSlice(slice);

	// Right pedal (inverted) to controller 17
	slice.minValue = OIS::JoyStick::MIN_AXIS;
	slice.maxValue = -257;
	slice.beginOutputValue = 128;
	slice.endOutputValue = 0;
	slice.controller = 17;
	pAxis->addSlice(slice);
}

MainWindow::~MainWindow()
{
	// Destroy the converter
	delete m_pConverter;

	saveSettings();
}


/******************
* Other functions *
******************/

void MainWindow::newFile()
{
	QMessageBox::information(this, "Not implemented yet!", "This function is not yet implemented...");
}

void MainWindow::openFile()
{
	QMessageBox::information(this, "Not implemented yet!", "This function is not yet implemented...");
}

void MainWindow::saveFile()
{
	QMessageBox::information(this, "Not implemented yet!", "This function is not yet implemented...");
}

void MainWindow::saveFileAs()
{
	QMessageBox::information(this, "Not implemented yet!", "This function is not yet implemented...");
}

void MainWindow::openRecentFile(QAction *pAction)
{
	QMessageBox::information(this, "Not implemented yet!", "This function is not yet implemented...");
}

void MainWindow::setStarted(bool started)
{
	assert(m_pConverter);

	//! @todo Make settings
	static const int interval = 20;
	static const int midiPort = 1;

	if(started)
	{
		if(m_pConverter->start((size_t) winId(), midiPort))
			m_timerId = startTimer(interval);
		else
			QMessageBox::warning(this, "Error starting converter", m_pConverter->getLastError().c_str());
	}
	else
	{
		killTimer(m_timerId);

		if(!m_pConverter->stop())
			QMessageBox::warning(this, "Error stopping converter", m_pConverter->getLastError().c_str());
	}
}

/**********************
* Protected functions *
**********************/

void MainWindow::timerEvent(QTimerEvent *pEvent)
{
	assert(m_pConverter);
	m_pConverter->update();
}

void MainWindow::createWidgets()
{
	// Add the designed widgets
	setupUi(this);

	// Connect to our code
	connect(action_New, SIGNAL(triggered()), SLOT(newFile()));
	connect(action_Open, SIGNAL(triggered()), SLOT(openFile()));
	connect(menuRecent_Files, SIGNAL(triggered(QAction *)), SLOT(openRecentFile(QAction *)));
	connect(action_Save, SIGNAL(triggered()), SLOT(saveFile()));
	connect(action_Save_As, SIGNAL(triggered()), SLOT(saveFileAs()));

	connect(action_About, SIGNAL(triggered()), SLOT(aboutDialog()));
	connect(actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

	connect(actionRun, SIGNAL(toggled(bool)), SLOT(setStarted(bool)));
}

void MainWindow::aboutDialog()
{
	QMessageBox::information(this,
		"About MidiMe",
		"This application can be used to easily convert OIS device input (mouse, keyboard, joysticks, ...) to midi signals.");
}

void MainWindow::loadSettings()
{
	// Get the application settings
	QSettings settings;
	settings.beginGroup("MainWindow");

	// Toolbar and docking widgets state
	if(settings.contains("state"))
		restoreState(settings.value("state").toByteArray());

	// Window settings
	if(settings.contains("position"))
		move(settings.value("Position").toPoint());
	if(settings.contains("size"))
		resize(settings.value("size").toSize());
	if(settings.value("maximized", false).toBool())
		showMaximized();

	settings.endGroup();

	// Update recent files
	updateRecentFiles();
}

void MainWindow::saveSettings()
{
	// Get the application settings
	QSettings settings;
	settings.beginGroup("MainWindow");

	// Toolbar and docking widgets state
	settings.setValue("state", saveState());

	// Window settings
	settings.setValue("position", pos());
	settings.setValue("size", size());
	settings.setValue("maximized", isMaximized());

	settings.endGroup();
}

/** Updates the recent files menu
	@todo Handle currently opened file
*/
void MainWindow::updateRecentFiles()
{
	// Note: the menu is created in designer
	QMenu *pMenu = menuRecent_Files;

	// Get the application settings
	QSettings settings;

	pMenu->clear();

	QStringList files = settings.value("recentFiles").toStringList();
	for(int i = 0; files.size(); ++i)
		pMenu->addAction(files.at(i));

	// Disable the menu when no files are present
	pMenu->setEnabled(!pMenu->isEmpty());
}
