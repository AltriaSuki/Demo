#include "element.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include<list>
#include"Shape.h"
extern wxColour color;
Element::~Element() {
	this->shapes.clear();
}
Element::Element(const Element& element) {
	for (auto& shape : element.shapes) {
		this->shapes.push_back(shape);
	}
	this->type = element.type;
	this->id = element.id;

}
Element& Element::operator=(const Element& element) {//�ú�����ǰ������ֵ�ǿյ�
	if (this == &element)return *this;
	for (auto& shape : element.shapes) {
		Shape newShape(shape.type,shape.start, shape.center, shape.end);
		this->shapes.push_back(newShape);
	}
	this->type = element.type;
	this->id = element.id;
	return *this;
}
bool Element::Select(const wxPoint& point) {
	isSelect = false;
	for (auto& shape : shapes) {
		if (shape.Contains(point)) {
			isSelect = true;
			break;
		}
	}
	if (isSelect) {
		return true;
	}
	else return false;
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
