// Includes
#include "global.h"
#include "MainWindow.h"
using namespace MidiMe;

#include <QtGui/QApplication>


/*! The application's main function */
int main(int argc, char *argv[])
{
	// Setup the application
	QApplication app(argc, argv);
	app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
	app.setOrganizationName("JeDiTech");
	app.setApplicationName("MidiMe");

	// create and show main window
	MainWindow window;
	window.show();

	// Start the application's main loop
	return app.exec();
}
