#include "element.h"

Element::Element(wxWindow* parent, const wxString& title)
    : wxButton(parent, wxID_ANY, title, wxPoint(100, 100))
{
    SetBackgroundColour(*wxWHITE);
    Bind(wxEVT_LEFT_DOWN, &Element::OnLeftDown, this);
    Bind(wxEVT_MOTION, &Element::OnMotion, this);
    Bind(wxEVT_LEFT_UP, &Element::OnLeftUp, this);
}

void Element::OnLeftDown(wxMouseEvent& event)
{
    isDragging = true;
    startpoint = event.GetPosition();
    CaptureMouse();
}

void Element::OnMotion(wxMouseEvent& event)
{
    if (isDragging)
    {
        wxPoint pos = event.GetPosition();
        wxPoint delta = pos - startpoint;
        Move(GetPosition() + delta);
    }
}

void Element::OnLeftUp(wxMouseEvent& event)
{
    if (isDragging)
    {
        isDragging = false;
        ReleaseMouse();
    }
}
