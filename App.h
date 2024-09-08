// Ensures the header file is included only once during compilation and includes the main wxWidgets header.
#pragma once
#include <wx/wx.h>

// Declares the App class, which inherits from wxApp. This makes App the main application class that manages
// the application’s life cycle, including initialization, event handling, and cleanup.
class App : public wxApp
{


// Declares the OnInit method, which is overridden from wxApp. This method is called when the application starts,
// and it is where the main application window (or frame) is usually created and shown.
public:
	bool OnInit();
};

