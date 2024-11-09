#pragma once
#include<wx/wx.h>
class Shape {
public:
	wxPoint start, center, end;
	wxPoint currentStart, currentEnd, currentCenter;
	std::string type;

	Shape(const std::string&t,const wxPoint&s,const wxPoint&c,const wxPoint&e)
		:type(t), start(s), center(c), end(e), currentStart(s), currentCenter(c), currentEnd(e) {
	}
	void Move(double offsetX, double offsetY);
	void DrawInit(wxDC& dc);
	void Draw(wxDC& dc);
	bool Contains(const wxPoint& point);
};