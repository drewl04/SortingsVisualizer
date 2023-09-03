#pragma once
#include "RectangleDrawing.h"

#include <wx/wx.h>
#include <wx/spinctrl.h>

#include <random>
#include <vector>

#define DEFAULT_ELEM_COUNT 25	// Number of rectangles that will be drawn on start
#define DEFAULT_MIN_VALUE 20	// Minimum height value (as a percentage of the screen) of a rectangle, dont set less than 0
#define DEFAULT_MAX_VALUE 100	// Maximum height value (as a percentage of the screen) of a rectangle, dont set over 100

class MainWindow : public wxFrame
{

public:
	/* vector of RectangleDrawing's GUI widgets, 
	* and a random device, needed for populating said vector with rectangles of varying heights,
	* that will be drawn to the screen with DrawBars() */
	std::vector<RectangleDrawing*> rectangles{};
	std::random_device rd;

	wxPanel* infoPanel;
	wxPanel* sidePanel;
	wxPanel* viewPanel;

	wxGridSizer* infoPanelWidgetsSizer;
	wxGridSizer* sidePanelWidgetsSizer;
	wxBoxSizer* viewPanelWidgetsSizer;

	wxBoxSizer* sideSizer; // sizer for 2 panels, infoPanel and sidePanel
	wxBoxSizer* mainSizer; // sizer for the sideSizer (infoPanel and sidePanel) and the viewPanel

	wxSpinCtrl* elementsAmountEntry;
	wxSpinCtrl* minValueEntry;
	wxSpinCtrl* maxValueEntry;

public:
	MainWindow(const wxString& title);

	void InitUI(); // initializes 3 panels (infoPanel, sidePanel, viewPanel), their sizers, the 2 main sizers (side and main) and populates those sizers with text, spincontrols, buttons and rectangles respectively
	void GenerateRectanglesToBeSorted(int minVal, int maxVal, int amount); // if the maxVal > minVal, clears the current vector of rectangles, then generates parameter amount of new rectangles, with different random heights, with interval minVal, maxVal
	void DrawBars(); // for every rectangle inside the rectangles vector, it adds it to the viewPanelWidgetsSizer
	void DestroyBars(); // destroys and empties objects inside the rectangles vector
	void RedrawBars(int minVal, int maxVal, int amount); // calls DestroyBars(), then GenerateRectanglesToBeSorted(), then DrawBars()
	void DisableAllButtons(); 
	void EnableAllButtons();
	wxColour LerpRedToGreen(int percentage); // depending on the rectangle height, which varies from 0 to 100 (%), it returns a color from red, to yellow, to green

	// clickable buttons
	void GenButtonClicked(wxCommandEvent& evt); // generates new rectangles, with minVal, maxVal and amount taken from the spincontrols

	/* for all the following buttons,
	* they disable all buttons,
	* then call their respective sorting algorithm inside the Rectangle Sorter class,
	* then enable all buttons */
	void BubbleButtonClicked(wxCommandEvent& evt); 
	void SelectionButtonClicked(wxCommandEvent& evt); 
	void InsertionButtonClicked(wxCommandEvent& evt); 
	void MergeRecursiveButtonClicked(wxCommandEvent& evt);  
	void MergeIterativeButtonClicked(wxCommandEvent& evt);  
	void QuickButtonClicked(wxCommandEvent& evt);  
	void PigeonholeButtonClicked(wxCommandEvent& evt);  

	wxDECLARE_EVENT_TABLE();

};


