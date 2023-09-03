#include "RectangleDrawing.h"
#include "MainWindow.h"

BEGIN_EVENT_TABLE(RectangleDrawing, wxPanel)
	EVT_PAINT(RectangleDrawing::PaintEvent)
	EVT_SIZE(RectangleDrawing::HandleResizing)
END_EVENT_TABLE()


RectangleDrawing::RectangleDrawing() {}

RectangleDrawing::RectangleDrawing(wxPanel* parent, wxPoint rectPosition, int rectHeightAsPercent, wxColour rectColor) : wxWindow(parent, wxID_ANY)
{
	position = rectPosition;
	color = rectColor;
	height = rectHeightAsPercent;
	SetMinSize(wxSize(MINIMUM_WIDTH, 0));
}

// private methods
void RectangleDrawing::PaintEvent(wxPaintEvent& evt)
{
	// depending on your system you may need to look at double-buffered 
	wxPaintDC dc(this);

	if (clearFlag)
		ClearRectangle(dc);
	else
		DrawRectangle(dc);
}

void RectangleDrawing::DrawRectangle(wxDC& dc)
{
	dc.SetBrush(wxBrush(color));
	dc.DrawRectangle(position.x, position.y, size.x, size.y);
}

void RectangleDrawing::ClearRectangle(wxDC& dc)
{
	dc.Clear();
}

void RectangleDrawing::HandleResizing(wxSizeEvent& evt)
{
	int viewPanelSize = evt.GetSize().y;
	int heightAmountToDraw = height * viewPanelSize / 100;

	Redraw(wxPoint(-1, viewPanelSize - heightAmountToDraw), wxSize(evt.GetSize().x, heightAmountToDraw), height, color);
}

// public methods
void RectangleDrawing::operator=(const RectangleDrawing& copy)
{
	clearFlag = copy.clearFlag;
	position = copy.position;
	color = copy.color;
	height = copy.height;
	size = copy.size;
}

void RectangleDrawing::ChangeClearFlag()
{
	clearFlag = !clearFlag;
}

void RectangleDrawing::Recolor(wxColour rectColor)
{
	ChangeClearFlag(); // clears the rectangles
	color = rectColor;
	ChangeClearFlag(); // redraws the rectangles with the new color
	this->Refresh();
}

void RectangleDrawing::Redraw(wxPoint rectPosition, wxSize rectSize, int rectHeightAsPercent, wxColour rectColor)
{
	ChangeClearFlag(); // clears the rectangles
	position = rectPosition;
	color = rectColor;
	size = rectSize;
	height = rectHeightAsPercent;
	ChangeClearFlag(); // redraws the rectangles with the new size
	this->Refresh();
}
