// Ensures the header file is included only once
// during compilation and includes the main wxWidgets header.
#pragma once
#include <wx/wx.h>


// Declares the AppFrame class, which inherits from wxFrame,
// making it a type of window or frame in wxWidgets.
class AppFrame : public wxFrame{


// Declares the constructor for AppFrame
// which takes a wxString title as an argument and initializes the frame.
public:
	AppFrame(const wxString& title);

// Declares the event handler for handling click events.
public:
	void onceClicked(wxCommandEvent& evt);

// Declares the event handler for handling back button click events.
public:
	void onceClickedBack(wxCommandEvent& evt);

public:
	void lumResult(wxCommandEvent& evt);

	void fluxResult(wxCommandEvent& evt);

public:
	void distanceEvent(wxCommandEvent& evt);

public:
	void luminosityEvent(wxCommandEvent& evt);

public:
	void fluxEvent(wxCommandEvent& evt);

//public:
	//void fluxResut(wxCommandEvent& evt);



private:

	// Declares a pointer to a wxTextCtrl for user input.
	wxTextCtrl* inputTextCtrl;
	wxTextCtrl* radiusInput;
	wxTextCtrl* tempInput;
	wxTextCtrl* luminosityInput;
	wxTextCtrl* distanceInput;

	// Declares a pointer to a wxStaticText for displaying results.
	wxStaticText* resultText;
	wxStaticText* lumResultText;
	wxStaticText* fluxResultText;

	//Explanation goes here:
	wxPanel* optionsPanel;

	// Declares a pointer to a wxPanel that contains the input controls.
	wxPanel* distancePanel;

	// Declares a pointer to a wxPanel that contains the result display controls.
	wxPanel* resultPanel;

	//Explanation goes here
	wxPanel* luminosityPanel;

	wxPanel* lumResultPanel;

	wxPanel* fluxPanel;

	wxPanel* fluxResultPanel;

	





// Creates a method that takes arcseconds, and converts to length in parsecs.
public:
	double findDistance(double input) {
		double distanceInParsecs = 1.0 / (input);
		return distanceInParsecs;
	}

	// Creates a method that takes parsecs, and converts to light years.
	double convertToLightYears(double distanceInParsecs) {
		double distanceInLightYears = distanceInParsecs * 3.26156378;
		return distanceInLightYears;
	}

	double convertToKm(double distanceInParsecs) {
		double distanceInKm = distanceInParsecs * 3.0857E+13;
		return distanceInKm;
	}

	double convertToM(double distanceInKm) {
		double distanceInM = distanceInKm * 1000;
		return distanceInM;
	}

	double luminosity(double radius, double temp) {
		double stefanBoltzmann = 5.67e-8;
		double pi = 3.14159265358979323846;

		double answer = 4 * pi * std::pow(radius, 2) * stefanBoltzmann * std::pow(temp, 4);

		return answer;
	}

	double solarLuminosity(double answer) {
		double conversion = answer / 3.826e26;
		return conversion;
	}

	double flux(double luminosity, double distance) {
		double pi = 3.14159265358979323846;
		double flux = luminosity / (4 * pi * (distance * distance));
		return flux;
	}
};



