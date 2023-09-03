#pragma once
#include "RectangleDrawing.h"

#include <wx/wx.h>
#include <wx/spinctrl.h>

#include <random>
#include <vector>

#define DEFAULT_ELEM_COUNT 25
#define DEFAULT_MIN_VALUE 20
#define DEFAULT_MAX_VALUE 100

class MainWindow : public wxFrame
{

public:
	std::vector<RectangleDrawing*> rectangles{};
	std::random_device rd;

	wxPanel* infoPanel;
	wxPanel* sidePanel;
	wxPanel* viewPanel;

	wxGridSizer* infoPanelWidgetsSizer;
	wxGridSizer* sidePanelWidgetsSizer;
	wxBoxSizer* viewPanelWidgetsSizer;

	wxBoxSizer* sideSizer; // Sizer for 2 panels, infoPanel and sidePanel
	wxBoxSizer* mainSizer; // Sizer for the sideSizer (infoPanel and sidePanel) and the viewPanel

	wxSpinCtrl* elementsAmountEntry;
	wxSpinCtrl* minValueEntry;
	wxSpinCtrl* maxValueEntry;

public:
	MainWindow(const wxString& title);

	void InitUI();
	void GenerateRectanglesToBeSorted(int minVal, int maxVal, int amount);
	void DrawBars();
	void DestroyBars();
	void RedrawBars(int minVal, int maxVal, int amount);
	void DisableAllButtons();
	void EnableAllButtons();
	wxColour LerpRedToGreen(int percentage);

	// Buttons
	void GenButtonClicked(wxCommandEvent& evt);
	void BubbleButtonClicked(wxCommandEvent& evt);
	void SelectionButtonClicked(wxCommandEvent& evt);
	void InsertionButtonClicked(wxCommandEvent& evt);
	void MergeRecursiveButtonClicked(wxCommandEvent& evt);
	void MergeIterativeButtonClicked(wxCommandEvent& evt);
	void QuickButtonClicked(wxCommandEvent& evt);
	void PigeonholeButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();

};


