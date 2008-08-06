// Includes
#include "MainWindow.h"
#include <libMidi-Me/DeviceManager.h>
#include <libMidi-Me/Chain.h>
using namespace MidiMe;

#include <QtCore/QSettings>
#include <QtGui/QMessageBox>
#include <QtGui/QInputDialog>
#include <QtCore/QTimer>
#include <QtGui/QCloseEvent>
#include <QtGui/QFileDialog>

// TEMP
#include "InputDeviceWidget.h"


//! The (hardcoded) maximum number of recently opened files
//! @todo Make this a setting
static const unsigned int s_numRecentFiles = 5;


/******************************
* Constructors and destructor *
******************************/

MainWindow::MainWindow()
: m_pChain(0), m_timerId(0)
{
	createWidgets();
	loadWindowSettings();

	// Create the converter
	m_pChain = new Chain();

#if 0
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
#endif

	// Add ourself as a device listener (to update the device menu)
	populateInputDeviceMenu();
	DeviceManager::getInstance().addListener(this);
	connect(menuInputDevice, SIGNAL(triggered(QAction *)), SLOT(selectInputDevice(QAction *)));
}

MainWindow::~MainWindow()
{
	// Remove ourself as a device listener
	DeviceManager::getInstance().removeListener(this);

	// Destroy the converter
	delete m_pChain;

	saveWindowSettings();
}


/******************
* Other functions *
******************/

void MainWindow::newFile()
{
	// Ask to save the current file if necessary
	if(!checkDirty()) return;

	QMessageBox::information(this, "Not implemented yet!", "This function is not yet implemented...");
}

void MainWindow::openFile()
{
	// Ask to save the current file if necessary
	if(!checkDirty()) return;

	// Ask for the filename
	QString filter = "Midi-Me files (*.mm)";
	QString filename = QFileDialog::getOpenFileName(this, "Open Midi-Me File", "", filter);
	if(filename.isNull()) return;

	// Load the settings
	if(!m_pChain->loadSettings(filename.toStdString()))
	{
		QString message = "Error loading from '" + filename + "': " + m_pChain->getLastError().c_str();
		QMessageBox::warning(this, "Error loading settings!", message);
	}
}

void MainWindow::saveFile()
{
	// If no current file yet, use save as dialog
	if(m_pChain->getCurrentFile().empty())
		return saveFileAs();

	// Save the settings
	if(!m_pChain->saveSettings())
	{
		QString message = QString("Error saving : ") + m_pChain->getLastError().c_str();
		QMessageBox::warning(this, "Error saving settings!", message);
	}
}

void MainWindow::saveFileAs()
{
	// Ask for the filename
	QString filter = "Midi-Me files (*.mm)";
	QString filename = QFileDialog::getSaveFileName(this, "Save Midi-Me File", "", filter);
	if(filename.isNull()) return;

	// Give a warning if the file exists already
	if(QFile::exists(filename))
	{
		int ret = QMessageBox::warning(this, tr("Midi-Me"),
			tr("File %1 already exists.\nDo you want to overwrite it?")
				.arg(QDir::convertSeparators(filename)),
			QMessageBox::Yes | QMessageBox::Default,
			QMessageBox::No | QMessageBox::Escape);

		if(ret == QMessageBox::No)
			return;
	}

	// Save the settings
	if(!m_pChain->saveSettings(filename.toStdString()))
	{
		QString message = "Error saving to '" + filename + "': " + m_pChain->getLastError().c_str();
		QMessageBox::warning(this, "Error saving settings!", message);
	}
}

void MainWindow::openRecentFile(QAction *pAction)
{
	// Ask to save the current file if necessary
	if(!checkDirty()) return;

	QMessageBox::information(this, "Not implemented yet!", "This function is not yet implemented...");
}

void MainWindow::setStarted(bool started)
{
	assert(m_pChain);

	//! @todo Make settings
	static const int interval = 20;

	if(started)
		m_timerId = startTimer(interval);
	else
		killTimer(m_timerId);
}

/**********************
* Protected functions *
**********************/

void MainWindow::timerEvent(QTimerEvent *pEvent)
{
	// Capture the input devices and generate events
	DeviceManager::getInstance().capture();
}

/* Intercept the close event for the window, to save the current file if needed */
void MainWindow::closeEvent(QCloseEvent *pEvent)
{
	if(!checkDirty())
		pEvent->ignore();

	pEvent->accept();
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

void MainWindow::loadWindowSettings()
{
	// Get the application settings
	QSettings settings;
	settings.beginGroup("MainWindow");

	// Window settings
	if(settings.contains("geometry"))
		restoreGeometry(settings.value("geometry").toByteArray());

	// Toolbar and docking widgets state
	if(settings.contains("state"))
		restoreState(settings.value("state").toByteArray());

	settings.endGroup();

	// Update recent files
	updateRecentFiles();
}

void MainWindow::saveWindowSettings()
{
	// Get the application settings
	QSettings settings;
	settings.beginGroup("MainWindow");

	// Window settings
	settings.setValue("geometry", saveGeometry());

	// Toolbar and docking widgets state
	settings.setValue("state", saveState());

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

/** Check if the current file has changes, and ask the user if he wants to save them.
	@return False when the user cancelled, so true if we should continue
*/
bool MainWindow::checkDirty()
{
	if(!m_pChain->isDirty())
		return true;

	int ret = QMessageBox::question(this, "Midi-Me",
		"The file has been modified.\nDo you want to save your changes?",
		QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
		QMessageBox::Cancel);
	
	if(ret == QMessageBox::Cancel)
		return false;

	else if(ret == QMessageBox::Save)
		saveFile();

	return true;
}

void MainWindow::onDeviceAdded(InputDevice *pDevice)
{
	menuInputDevice->addAction(pDevice->getName().c_str());
}

void MainWindow::onDeviceRemoving(InputDevice *pDevice)
{
	QList<QAction *> actions = menuInputDevice->actions();
	QAction *pAction = 0;
	
	for(int i = 0; i < actions.size() && !pAction; ++i)
	{
		if(actions.at(i)->text().toStdString() == pDevice->getName())
			pAction = actions.at(i);
	}

	if(pAction)
		removeAction(pAction);
}

void MainWindow::populateInputDeviceMenu()
{
	menuInputDevice->clear();

	const InputDeviceMap &devices = DeviceManager::getInstance().getInputDevices();
	InputDeviceMap::const_iterator it;
	for(it = devices.begin(); it != devices.end(); ++it)
		menuInputDevice->addAction(it->second->getName().c_str());
}

void MainWindow::selectInputDevice(QAction *pAction)
{
	InputDevice *pDevice = DeviceManager::getInstance().getInputDevice(pAction->text().toStdString());
	if(pDevice)
	{
		// Show the device input widget
		InputDeviceWidget *pDevWidget = new InputDeviceWidget(pDevice, this);
		pDevWidget->setAttribute(Qt::WA_DeleteOnClose);
		pDevWidget->show();
	}
}
