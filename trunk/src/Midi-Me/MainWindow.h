#ifndef MIDIME_MAINWINDOW_H
#define MIDIME_MAINWINDOW_H

// Includes
#include "global.h"
#include "MainWindowBase.h"

namespace MidiMe
{
	// Forward declarations
	class ConverterManager;

	/** The main window of our OIS 2 midi application
		@todo Maximum number of recent files (setting)
		@todo Check if file dirty, add asteriks to title bar and ask to save when opening or quitting
	*/
	class MainWindow : public QMainWindow, private Ui::MainWindowBase
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

	protected:
		// Events
		void timerEvent(QTimerEvent *pEvent);

		void createWidgets();
		void loadSettings();
		void saveSettings();
		void updateRecentFiles();

		// Member variables
		ConverterManager *m_pConverter;
		int m_timerId;
	};
}

#endif // MIDIME_MAINWINDOW_H
