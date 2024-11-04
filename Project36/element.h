#pragma once
#include<wx/wx.h>
#include<list>
#include"Shape.h"
class Element {
public:
	
	Element() {};
	bool Select(const wxPoint& point);
	void MoveSelected(const wxPoint& point);
	void DeselectAll();
	void DeleteSelected();
	void StartDragging(const wxPoint& point);
	void EndDragging(const wxPoint& point);
	void UpdateDragging(const wxPoint& point);
	bool isSelect = false;
	std::list<Shape> shapes;

	bool isDragging = false;
	wxPoint startpoint, endpoint;
};