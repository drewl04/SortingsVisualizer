#pragma once
#include <wx/wx.h>

#define MINIMUM_WIDTH 10

class RectangleDrawing : public wxWindow
{
private:
	bool clearFlag = false;

public:
	wxPoint position;
	wxColour color;
	int height;
	wxSize size;

private:
	void PaintEvent(wxPaintEvent& evt);
	void DrawRectangle(wxDC& dc);
	void ClearRectangle(wxDC& dc);
	void HandleResizing(wxSizeEvent& evt);

public:
	RectangleDrawing();
	RectangleDrawing(wxPanel* parent, wxPoint rectPosition, int rectHeightAsPercent, wxColour rectColor);

	void operator=(const RectangleDrawing& copy);
	void ChangeClearFlag();
	void Recolor(wxColour rectColor);
	void Redraw(wxPoint rectPosition, wxSize rectSize, int rectHeightAsPercent, wxColour rectColor);

	DECLARE_EVENT_TABLE()

};