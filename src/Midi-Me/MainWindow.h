#ifndef MIDIME_MAINWINDOW_H
#define MIDIME_MAINWINDOW_H

// Includes
#include "global.h"
#include "MainWindowBase.h"
#include <libMidi-Me/DeviceManager.h>

namespace MidiMe
{
	// Forward declarations
	class Chain;
	class ChainWidget;

	/** The main window of our OIS 2 midi application
		@todo Check if file dirty, add asteriks to title bar and ask to save when opening or quitting
	*/
	class MainWindow : public QMainWindow, private Ui::MainWindowBase, protected DeviceManager::Listener
	{
		Q_OBJECT

	public:
		// Constructors and destructor
		MainWindow();
		virtual ~MainWindow();

	public slots:
		void newFile();
		void openFile();
		void saveFile();
		void saveFileAs();
		void aboutDialog();
		
		void setStarted(bool started);

	protected slots:
		void openRecentFile(QAction *pAction);
		void populateInputDeviceMenu();
		void selectInputDevice(QAction *pAction);
		void populateMidiOutMenu();
		void selectMidiOut(QAction *pAction);

	protected:
		// Events
		void timerEvent(QTimerEvent *pEvent);
		void closeEvent(QCloseEvent *pEvent);

		// DeviceManager::Listener functions
		void onDeviceAdded(InputDevice *pDevice);
		void onDeviceRemoving(InputDevice *pDevice);

		void createWidgets();
		void loadWindowSettings();
		void saveWindowSettings();
		void updateRecentFiles();
		bool checkDirty();

		// Member variables
		Chain *m_pChain;
		ChainWidget *m_pChainEditor;
		int m_timerId;
	};
}

#endif // MIDIME_MAINWINDOW_H
