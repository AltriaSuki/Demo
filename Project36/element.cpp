#include "element.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <vector>
void Element::Select(const wxPoint& point) {
	wxRect rect;
	for (auto& shape : shapes) {
		if (shape.Contains(point)) {
			isSelect = true;
			break;
		}
	}
}
void Element::ChangeColor(wxDC& dc) {
	if (isSelect) {
		for (auto& shape : shapes) {
			if (shape.Contains(startpoint)) {
				dc.SetPen(*wxRED_PEN);
				shape.Draw(dc);
			}
			else {
				dc.SetPen(*wxBLACK_PEN);
				shape.Draw(dc);
			}
		}
	}
	else {
		for (auto& shape : shapes) {
			dc.SetPen(*wxBLACK_PEN);
			shape.Draw(dc);
		}
	}
}
void Element::MoveSelected(const wxPoint& point) {
	if (isSelect) {
		wxPoint delta = point - startpoint;
		for (auto& shape : shapes) {
			if (shape.Contains(startpoint)) {
				shape.start += delta;
				shape.center += delta;
				shape.end += delta;
			}
		}
		startpoint = point;
	}
}
void Element::DeselectAll() {
	isSelect = false;
}

void Element::DeleteSelected() {
	if (isSelect) {
		for (auto it = shapes.begin(); it != shapes.end(); ++it) {
			if (it->Contains(startpoint)) {
				shapes.erase(it);
				break;
			}
		}
	}
}
void Element::StartDragging(const wxPoint& point) {
	isDragging = true;
	startpoint = point;
}
void Element::EndDragging(const wxPoint& point) {
	isDragging = false;
}
void Element::UpdateDragging(const wxPoint& point) {
	if (isDragging) {
		endpoint = point;
	}
}


























//
//Element::Element(wxWindow* parent, const wxString& title)
//    : wxButton(parent, wxID_ANY, title, wxPoint(100, 100))
//{
//    SetBackgroundColour(*wxWHITE);
//    Bind(wxEVT_LEFT_DOWN, &Element::OnLeftDown, this);
//    Bind(wxEVT_MOTION, &Element::OnMotion, this);
//    Bind(wxEVT_LEFT_UP, &Element::OnLeftUp, this);
//}
//
//void Element::OnLeftDown(wxMouseEvent& event)
//{
//    isDragging = true;
//    startpoint = event.GetPosition();
//    CaptureMouse();
//}
//
//void Element::OnMotion(wxMouseEvent& event)
//{
//    if (isDragging)
//    {
//        wxPoint pos = event.GetPosition();
//        wxPoint delta = pos - startpoint;
//        Move(GetPosition() + delta);
//    }
//}
//
//void Element::OnLeftUp(wxMouseEvent& event)
//{
//    if (isDragging)
//    {
//        isDragging = false;
//        ReleaseMouse();
//    }
//}
