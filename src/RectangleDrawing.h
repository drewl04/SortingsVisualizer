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

	/* height is set when the constructor is called, and is between 0-100,
	* it determines how tall should the rectangle be relative to the screen size,
	* whereas size is used to determine what actual size to draw it on the screen, 
	* depending on the screen size, size is set by HandleResizing() */
	int height;
	wxSize size;

private:
	void PaintEvent(wxPaintEvent& evt); // this function is called every frame, and depending on whether clearFlag is true or false, it either DrawRectangle() or ClearRectangle()
	void DrawRectangle(wxDC& dc);
	void ClearRectangle(wxDC& dc);
	void HandleResizing(wxSizeEvent& evt); // resizes the rectangle as the user resizes the screen (maintains a minimum width of MINIMUM_WIDTH)

public:
	RectangleDrawing();
	RectangleDrawing(wxPanel* parent, wxPoint rectPosition, int rectHeightAsPercent, wxColour rectColor);

	void operator=(const RectangleDrawing& copy);
	void ChangeClearFlag();
	void Recolor(wxColour rectColor);
	void Redraw(wxPoint rectPosition, wxSize rectSize, int rectHeightAsPercent, wxColour rectColor);

	DECLARE_EVENT_TABLE()

};