#include "AppFrame.h"
#include <wx/wx.h>


//AppFrame Constructor. This is what the user sees.
AppFrame::AppFrame(const wxString& title) :
	 wxFrame(NULL, wxID_ANY, title)
{
    //Custom Icon at top left of window.
	wxIcon icon;
	icon.LoadFile("C:/Users/natha/icon.png", wxBITMAP_TYPE_PNG);
	SetIcon(icon);

    //Explanation goes here:
    optionsPanel = new wxPanel(this, wxID_ANY);
    wxStaticText* options = new wxStaticText(optionsPanel, wxID_ANY, "What do you want to find?", wxPoint(120, 150));
    wxButton* distance = new wxButton(optionsPanel, wxID_ANY, "Distance", wxPoint(400, 300), wxSize(100, 25));
    distance->Bind(wxEVT_BUTTON, &AppFrame::distanceEvent, this);
    wxButton* luminosity = new wxButton(optionsPanel, wxID_ANY, "Luminosity", wxPoint(400, 250), wxSize(100, 25));
    luminosity->Bind(wxEVT_BUTTON, &AppFrame::luminosityEvent, this);
    wxButton* na = new wxButton(optionsPanel, wxID_ANY, "Submit", wxPoint(400, 200), wxSize(100, 25));

    //Input Panel for initial view. 
	distancePanel = new wxPanel(this, wxID_ANY);
    wxStaticText* angleInput = new wxStaticText(distancePanel, wxID_ANY, "Please enter the parallax angle (in arc seconds)", wxPoint(120, 150));
	wxButton* button = new wxButton(distancePanel, wxID_ANY, "Submit", wxPoint(400, 300), wxSize(100, 25));
    button->Bind(wxEVT_BUTTON, &AppFrame::onceClicked, this);
	inputTextCtrl = new wxTextCtrl(distancePanel, wxID_ANY, "", wxPoint(250, 250), wxSize(150, -1));

    //Result Panel for result view.
    resultPanel = new wxPanel(this, wxID_ANY);
    resultPanel->Hide(); 
    resultText = new wxStaticText(resultPanel, wxID_ANY, "", wxPoint(20, 20), wxDefaultSize, wxALIGN_LEFT);
    wxButton* backButton = new wxButton(resultPanel, wxID_ANY, "Back", wxPoint(400, 300), wxSize(100, 25));
    backButton->Bind(wxEVT_BUTTON, &AppFrame::onceClickedBack, this);

    luminosityPanel = new wxPanel(this, wxID_ANY);
    wxStaticText* metersPrompt = new wxStaticText(luminosityPanel, wxID_ANY, "Enter the radius of the star in Meters.", wxPoint(120, 150));
    radiusInput = new wxTextCtrl(luminosityPanel, wxID_ANY, "", wxPoint(250, 170), wxSize(150, -1));
    wxStaticText* kelvinPrompt = new wxStaticText(luminosityPanel, wxID_ANY, "Enter the temperature of the star in Kelvin.", wxPoint(120, 210));
    tempInput = new wxTextCtrl(luminosityPanel, wxID_ANY, "", wxPoint(250, 250), wxSize(150, -1));
    wxButton* submit = new wxButton(luminosityPanel, wxID_ANY, "Submit", wxPoint(400, 300), wxSize(100, 25));
    submit->Bind(wxEVT_BUTTON, &AppFrame::lumResult, this);

    lumResultPanel = new wxPanel(this, wxID_ANY);
    lumResultPanel->Hide();
    lumResultText = new wxStaticText(resultPanel, wxID_ANY, "", wxPoint(20, 20), wxDefaultSize, wxALIGN_LEFT);


    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(optionsPanel, 1, wxEXPAND);
    sizer->Add(distancePanel, 1, wxEXPAND);
    sizer->Add(resultPanel, 1, wxEXPAND);
    sizer->Add(luminosityPanel, 1, wxEXPAND);
    sizer->Add(lumResultPanel, 1, wxEXPAND);
    SetSizer(sizer);

    // Ensure the options panel is shown first.
    optionsPanel->Show();
    distancePanel->Hide();
    luminosityPanel->Hide();
    lumResultPanel->Hide();

    Layout();
    
}
// Begining of the event handler for the submit button clicked event.
void AppFrame::onceClicked(wxCommandEvent& evt) {

    // Retrieves the text input from the wxTextCtrl (inputTextCtrl) and stores it as inputStr.
	wxString inputStr = inputTextCtrl->GetValue();

    // Attempt to convert the string input (inputStr) into a double (inputValue). 
    // If the conversion is successful, proceed with the calculations.
	double inputValue;
	if (inputStr.ToDouble(&inputValue)) {

        //Calls the findDistance function, passing the input value.
        //and calculates the corresponding distance in parsecs.
        double distanceInParsecs = findDistance(inputValue);

        // Convert the calculated distance in parsecs to light years using convertToLightYears function.
        double distanceInLightYears = convertToLightYears(distanceInParsecs);

     //Formats the results as a string with 6 decimal percision.
        wxString resultString = wxString::Format(
            "Distance in Parsecs: %.6f\nDistance in Light Years: %.6f",
            distanceInParsecs, distanceInLightYears);

        // Update the label of the wxStaticText control (resultText) 
        //to display the formatted result string (resultString).
        //Without this, the output would not show at all.
        //SYNTAX NOTE: resultText->SetLabe(...); in C++, is the same as 
        //resultText.setLabel(...); in Java.
        resultText->SetLabel(resultString);

        //Hides the input panel and shows the result panel.
        distancePanel->Hide();
        resultPanel->Show();
     
        // Adjust layout after showing/hiding panels
        Layout(); 
    }

    // If the conversion of the input string to a double fails, show an error message box to the user using wxMessageBox, 
    // indicating that the input was invalid.
    else {
        wxMessageBox("Invalid input. Please enter a valid number.", "Error", wxOK | wxICON_ERROR);
    }
}


//Event handler that, when the back button is clicked, hides the result panel and once again shows
//the input panel.
void AppFrame::onceClickedBack(wxCommandEvent& evt) {

    lumResultPanel->Hide();
    resultPanel->Hide();
    //distancePanel->Show();
    optionsPanel->Show();

}

void AppFrame::distanceEvent(wxCommandEvent& evt) {
    optionsPanel->Hide();
    distancePanel->Show();
}

void AppFrame::luminosityEvent(wxCommandEvent& evt) {
    optionsPanel->Hide();
    luminosityPanel->Show();
}

void AppFrame::lumResult(wxCommandEvent& evt) {
    wxString radiusStr = inputTextCtrl->GetValue();
    wxString tempStr = inputTextCtrl->GetValue();

    double radiusInput;
    double tempInput;
    if (radiusStr.ToDouble(&radiusInput) && tempStr.ToDouble(&tempInput)) {

        double luminosityOfStar = luminosity(radiusInput, tempInput);

        double lumInSolLums = solarLuminosity(luminosityOfStar);

        wxString resultString = wxString::Format(
            "Luminosity in Watts: %.6f\nLuminosity in Solar Luminosities: %.6f",
            luminosityOfStar, lumInSolLums);

        lumResultText->SetLabel(resultString);


        luminosityPanel->Hide();
        resultPanel->Show();

        Layout();
    }

    else {
        wxMessageBox("Invalid input. Please enter a valid number.", "Error", wxOK | wxICON_ERROR);
    }
    


}