// Includes necessary headers. "App.h" and "AppFrame.h" custom classes, 
// and <wx/wx.h> is the main wxWidgets header.
#include "App.h"
#include "AppFrame.h"
#include <wx/wx.h>

// Declares App as the main application class and sets up the entry point for the program.
wxIMPLEMENT_APP(App);

// Initializes the application when it starts.
bool App::OnInit() {

	// Initializes all image handlers to support different image formats.
	wxInitAllImageHandlers();
	
	// Creates a new instance of AppFrame, which is the main window, and sets its title.
	AppFrame* appFrame = new AppFrame("Star Distance Calculator");

	// Sets the size of the main window's client area to 600x400 pixels.
	appFrame->SetSizeHints(wxSize(600, 400), wxSize(600, 400));

	// Centers the main window on the screen.
	appFrame->Center();

	// Makes the main window visible.
	appFrame->Show();


	// Indicates that initialization was successful, allowing the application to continue running.
	return true;
}