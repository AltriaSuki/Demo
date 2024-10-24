#pragma once
#include<wx/wx.h>
class Shape {
public:
	wxPoint start, center, end;
	std::string type;
	Shape(const std::string&t,const wxPoint&s,const wxPoint&c,const wxPoint&e)
		:type(t),start(s),center(c),end(e){ }
	void Draw(wxDC& dc);
	bool Contains(const wxPoint& point);
};