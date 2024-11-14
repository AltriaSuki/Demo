#pragma once
#include<wx/wx.h>
#include"Shape.h"
#include<list>

class Line {
public:
	std::list<Shape> shapes;
	Line() :id(0) {};
	Line(const Line& line);
	Line& operator=(const Line& line);
	bool Select(const wxPoint& point);
	int id;

};