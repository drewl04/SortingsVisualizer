#include "MainWindow.h"
#include "RectangleDrawing.h"
#include "RectangleSorter.h"

enum IDs
{
	GEN_BUTTON_ID,
	BUBBLE_BUTTON_ID,
	SELECTION_BUTTON_ID,
	INSERTION_BUTTON_ID,
	MERGE_RECURSIVE_BUTTON_ID,
	MERGE_ITERATIVE_BUTTON_ID,
	QUICK_BUTTON_ID,
	PIGEONHOLE_BUTTON_ID
};

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
	EVT_BUTTON(GEN_BUTTON_ID, MainWindow::GenButtonClicked)
	EVT_BUTTON(BUBBLE_BUTTON_ID, MainWindow::BubbleButtonClicked)
	EVT_BUTTON(SELECTION_BUTTON_ID, MainWindow::SelectionButtonClicked)
	EVT_BUTTON(INSERTION_BUTTON_ID, MainWindow::InsertionButtonClicked)
	EVT_BUTTON(MERGE_RECURSIVE_BUTTON_ID, MainWindow::MergeRecursiveButtonClicked)
	EVT_BUTTON(MERGE_ITERATIVE_BUTTON_ID, MainWindow::MergeIterativeButtonClicked)
	EVT_BUTTON(QUICK_BUTTON_ID, MainWindow::QuickButtonClicked)
	EVT_BUTTON(PIGEONHOLE_BUTTON_ID, MainWindow::PigeonholeButtonClicked)
wxEND_EVENT_TABLE()


MainWindow::MainWindow(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	InitUI();
	GenerateRectanglesToBeSorted(DEFAULT_MIN_VALUE, DEFAULT_MAX_VALUE, DEFAULT_ELEM_COUNT);
	DrawBars();

	// creates status bar, where the number of comparisons, array accesses, and ms delay are shown
	this->CreateStatusBar(); 
}

void MainWindow::InitUI()
{
	infoPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	sidePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	viewPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	infoPanelWidgetsSizer = new wxGridSizer(4, 3, 0, 0);
	sidePanelWidgetsSizer = new wxGridSizer(7, 0, 0, 0);
	viewPanelWidgetsSizer = new wxBoxSizer(wxHORIZONTAL);

	sideSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer = new wxBoxSizer(wxHORIZONTAL);

	sideSizer->Add(infoPanel, 1, wxEXPAND, 5);
	sideSizer->Add(sidePanel, 5, wxEXPAND | wxTOP, 5);

	mainSizer->Add(sideSizer, 1, wxEXPAND | wxLEFT | wxTOP | wxBOTTOM, 5);
	mainSizer->Add(viewPanel, 7, wxEXPAND | wxALL, 5);

	infoPanel->SetSizerAndFit(infoPanelWidgetsSizer);
	sidePanel->SetSizerAndFit(sidePanelWidgetsSizer);
	viewPanel->SetSizerAndFit(viewPanelWidgetsSizer);
	this->SetSizerAndFit(mainSizer);

	// widgets for the infoPanel sizer and sidePanel sizer
	wxStaticText* elementsAmountLabel = new wxStaticText(infoPanel, wxID_ANY, "Count", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
	wxStaticText* minElementValueLabel = new wxStaticText(infoPanel, wxID_ANY, "Min", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
	wxStaticText* maxElementValueLabel = new wxStaticText(infoPanel, wxID_ANY, "Max", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
	elementsAmountEntry = new wxSpinCtrl(infoPanel, wxID_ANY, std::to_string(DEFAULT_ELEM_COUNT));
	minValueEntry = new wxSpinCtrl(infoPanel, wxID_ANY, std::to_string(DEFAULT_MIN_VALUE));
	maxValueEntry = new wxSpinCtrl(infoPanel, wxID_ANY, std::to_string(DEFAULT_MAX_VALUE));
	wxStaticText* emptyLabel1 = new wxStaticText(infoPanel, wxID_ANY, ""); 
	wxStaticText* emptyLabel2 = new wxStaticText(infoPanel, wxID_ANY, ""); 
	wxStaticText* emptyLabel3 = new wxStaticText(infoPanel, wxID_ANY, "");  
	wxStaticText* emptyLabel4 = new wxStaticText(infoPanel, wxID_ANY, ""); 
	wxButton* genButton = new wxButton(infoPanel, GEN_BUTTON_ID, "Gen");

	wxButton* bubbleSortButton = new wxButton(sidePanel, BUBBLE_BUTTON_ID, "Bubble Sort");
	wxButton* selectionSortButton = new wxButton(sidePanel, SELECTION_BUTTON_ID, "Selection Sort");
	wxButton* insertionSortButton = new wxButton(sidePanel, INSERTION_BUTTON_ID, "Insertion Sort");
	wxButton* mergeSortRecursiveButton = new wxButton(sidePanel, MERGE_RECURSIVE_BUTTON_ID, "Merge Sort\n" "- recursive -");
	wxButton* mergeSortIterativeButton = new wxButton(sidePanel, MERGE_ITERATIVE_BUTTON_ID, "Merge Sort\n" "- iterative -");
	wxButton* quickSortButton = new wxButton(sidePanel, QUICK_BUTTON_ID, "Quick Sort\n" "(R Pivot)\n");
	wxButton* pigeonholeSortButton = new wxButton(sidePanel, PIGEONHOLE_BUTTON_ID, "Pigeonhole Sort");

	infoPanelWidgetsSizer->Add(elementsAmountLabel, 0, wxEXPAND | wxALL);
	infoPanelWidgetsSizer->Add(emptyLabel1, 1, wxEXPAND | wxALL);
	infoPanelWidgetsSizer->Add(elementsAmountEntry, 2, wxEXPAND | wxALL);
	infoPanelWidgetsSizer->Add(minElementValueLabel, 3, wxEXPAND | wxALL);
	infoPanelWidgetsSizer->Add(emptyLabel2, 4, wxEXPAND | wxALL);
	infoPanelWidgetsSizer->Add(minValueEntry, 5, wxEXPAND | wxALL);
	infoPanelWidgetsSizer->Add(maxElementValueLabel, 6, wxEXPAND | wxALL);
	infoPanelWidgetsSizer->Add(emptyLabel3, 7, wxEXPAND | wxALL);
	infoPanelWidgetsSizer->Add(maxValueEntry, 8, wxEXPAND | wxALL);
	infoPanelWidgetsSizer->Add(emptyLabel4, 9, wxEXPAND | wxALL);
	infoPanelWidgetsSizer->Add(genButton, 10, wxEXPAND | wxALL);

	sidePanelWidgetsSizer->Add(bubbleSortButton, 0, wxEXPAND | wxALL);
	sidePanelWidgetsSizer->Add(selectionSortButton, 1, wxEXPAND | wxALL);
	sidePanelWidgetsSizer->Add(insertionSortButton, 2, wxEXPAND | wxALL);
	sidePanelWidgetsSizer->Add(mergeSortRecursiveButton, 3, wxEXPAND | wxALL);
	sidePanelWidgetsSizer->Add(mergeSortIterativeButton, 4, wxEXPAND | wxALL);
	sidePanelWidgetsSizer->Add(quickSortButton, 5, wxEXPAND | wxALL);
	sidePanelWidgetsSizer->Add(pigeonholeSortButton, 6, wxEXPAND | wxALL);
}

void MainWindow::GenerateRectanglesToBeSorted(int minVal, int maxVal, int amount)
{	
	if (minVal > maxVal) return;

	rectangles.clear();

	std::uniform_int_distribution<int> values_interval(minVal, maxVal);
	int currentRandValue;

	for (int i{ 0 }; i < amount; i++)
	{
		// stores the random value given by the random device, then pushes a new rectangle object in the vector with its height as the random value, and calculates its color also based on that stored random value
		currentRandValue = values_interval(rd);
		rectangles.push_back(new RectangleDrawing(viewPanel, wxDefaultPosition, currentRandValue, LerpRedToGreen(currentRandValue)));
	}
}

void MainWindow::DrawBars()
{
	for (int i{ 0 }; i < rectangles.size(); ++i)
	{
		viewPanelWidgetsSizer->Add(rectangles[i], 1, wxEXPAND);
	}
	this->Layout();
}

void MainWindow::DestroyBars()
{
	for (int i{ 0 }; i < rectangles.size(); ++i)
	{
		rectangles[i]->Destroy();
	}
	rectangles.clear();
}

void MainWindow::RedrawBars(int minVal, int maxVal, int amount)
{
	if (minVal > maxVal) return;
	this->DestroyBars();
	GenerateRectanglesToBeSorted(minVal, maxVal, amount);
	this->DrawBars();
}

void MainWindow::DisableAllButtons()
{
	/* iterates through the widgets inside infoPanelWidgetsSizer and sidePanelWidgetsSizer,
	if that widget has a button ID, it disables it */

	for (auto widget : infoPanelWidgetsSizer->GetChildren())
	{
		if (widget->GetWindow()->GetId() == GEN_BUTTON_ID)
			widget->GetWindow()->Disable();
	}
	for (auto button : sidePanelWidgetsSizer->GetChildren())
	{
		button->GetWindow()->Disable();
	}
}

void MainWindow::EnableAllButtons()
{
	/* iterates through the widgets inside infoPanelWidgetsSizer and sidePanelWidgetsSizer,
	if that widget has a button ID, it enables it */

	for (auto widget : infoPanelWidgetsSizer->GetChildren())
	{
		if (widget->GetWindow()->GetId() == GEN_BUTTON_ID)
			widget->GetWindow()->Enable();
	}
	for (auto button : sidePanelWidgetsSizer->GetChildren())
	{
		button->GetWindow()->Enable();
	}
}

wxColour MainWindow::LerpRedToGreen(int percentage)
{
	if (percentage > 50)
	{
		// the more the percentage is above 50, the more it substracts from the red channel, at 100, it is fully green with no red
		return wxColour(255 - (percentage - 50) * 5, 255, 0);
	}

	// the more the percentage is below 50, the more it substracts from the green channel, at 0, it is fully red with no green
	return wxColour(255, 255 - (50 - percentage) * 5, 0);  
}

// clickable buttons implementations
void MainWindow::GenButtonClicked(wxCommandEvent& evt)
{
	// clears the status bar
	wxLogStatus("");
	RedrawBars(minValueEntry->GetValue(), maxValueEntry->GetValue(), elementsAmountEntry->GetValue());
}

void MainWindow::BubbleButtonClicked(wxCommandEvent& evt)
{
	DisableAllButtons();
	RectangleSorter::BubbleSort(rectangles);
	EnableAllButtons();
}

void MainWindow::SelectionButtonClicked(wxCommandEvent& evt)
{
	DisableAllButtons();
	RectangleSorter::SelectionSort(rectangles);
	EnableAllButtons();
}

void MainWindow::InsertionButtonClicked(wxCommandEvent& evt)
{
	DisableAllButtons();
	RectangleSorter::InsertionSort(rectangles);
	EnableAllButtons();
}

void MainWindow::MergeRecursiveButtonClicked(wxCommandEvent& evt) 
{
	/* clears the status bar and resets comparisons and
	* array accesses amount, then writes them to the screen after the sort,
	* as these things could not have been done
	* inside a recursive function */
	DisableAllButtons();
	wxLogStatus("");
	RectangleSorter::comparisons = 0;
	RectangleSorter::arrayAccesses = 0;
	RectangleSorter::MergeSortRecursive(rectangles, 0, rectangles.size()-1);

	wxString comparisonsWXString = wxString::Format(wxT("%i"), RectangleSorter::comparisons);
	wxString arrayAccessesWXString = wxString::Format(wxT("%i"), RectangleSorter::arrayAccesses);
	wxString sortDelayWXString = wxString::Format(wxT("%i"), SORT_DELAY);
	wxLogStatus("Merge Sort (Recursive) - " + comparisonsWXString + " comparisons, " + arrayAccessesWXString + " array accesses, " + sortDelayWXString + " ms delay");
	EnableAllButtons();
}

void MainWindow::MergeIterativeButtonClicked(wxCommandEvent& evt)
{
	DisableAllButtons();
	RectangleSorter::MergeSortIterative(rectangles);
	EnableAllButtons();
}

void MainWindow::QuickButtonClicked(wxCommandEvent& evt)
{
	/* clears the status bar and resets comparisons and
	* array accesses amount, then writes them to the screen after the sort,
	* as these things could not have been done
	* inside a recursive function */
	DisableAllButtons();
	wxLogStatus("");
	RectangleSorter::comparisons = 0;
	RectangleSorter::arrayAccesses = 0;
	RectangleSorter::QuickSort(rectangles, 0, rectangles.size()-1);

	wxString comparisonsWXString = wxString::Format(wxT("%i"), RectangleSorter::comparisons);
	wxString arrayAccessesWXString = wxString::Format(wxT("%i"), RectangleSorter::arrayAccesses);
	wxString sortDelayWXString = wxString::Format(wxT("%i"), SORT_DELAY);
	wxLogStatus("Quick Sort (R Pivot) - " + comparisonsWXString + " comparisons, " + arrayAccessesWXString + " array accesses, " + sortDelayWXString + " ms delay");
	EnableAllButtons();
}

void MainWindow::PigeonholeButtonClicked(wxCommandEvent& evt)
{
	DisableAllButtons();
	RectangleSorter::PigeonholeSort(rectangles);
	EnableAllButtons();

	/* after it has sorted the rectangles inside the rectangle vector, based off height,
	* it clears the viewPanelWidgetsSizer displaying the old rectangles,
	* then adds them again and updates the screen */
	viewPanelWidgetsSizer->Clear(true); 

	for (int i{ 0 }; i < rectangles.size(); ++i)
	{
		viewPanelWidgetsSizer->Add(rectangles[i], 1, wxEXPAND);
		this->Layout();
		wxYield(); // clears/updates the DC buffer, without this, changes in rectangle's color, height or position would not be visible
	}
}