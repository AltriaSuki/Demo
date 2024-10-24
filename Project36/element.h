#pragma once
#include<wx/wx.h>
#include<vector>
#include"Shape.h"
class Element {
public:
	std::vector<Shape> shapes;
	Element() {}
	void Select(const wxPoint& point);
	void ChangeColor(wxDC& dc);
	void MoveSelected(const wxPoint& point);
	void DeselectAll();
	void DeleteSelected();
	void StartDragging(const wxPoint& point);
	void EndDragging(const wxPoint& point);
	void UpdateDragging(const wxPoint& point);
	bool isSelect = false;
private:
	bool isDragging = false;
	wxPoint startpoint, endpoint;
};