#pragma once
#include<wx/wx.h>
#include<list>
#include"Shape.h"
class Element {
public:
	
	Element() :type(0), id(0), isDragging(false),isSelect(false) {};
	Element(const Element& element);
	Element& operator=(const Element& element);
	bool Select(const wxPoint& point);
	void MoveSelected(const wxPoint& point);
	void DeselectAll();
	void DeleteSelected();
	void StartDragging(const wxPoint& point);
	void EndDragging(const wxPoint& point);
	void UpdateDragging(const wxPoint& point);
	bool isSelect = false;
	std::list<Shape> shapes;

	int type;
	int id;
	bool isDragging;
	wxPoint startpoint, endpoint;
};