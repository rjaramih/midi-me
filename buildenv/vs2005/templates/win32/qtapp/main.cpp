// Includes
#include "global.h"
#include <QtGui/QApplication>


/*! The application's main function */
int main(int argc, char *argv[])
{
	// Create a QT application
	QApplication app(argc, argv);


	// TODO: Typically create a main window and show it


	// Make sure the app quits when we close the last window
	app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));

	// Execute the application
	return app.exec();
}
