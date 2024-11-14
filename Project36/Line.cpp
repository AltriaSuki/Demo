#include"Line.h"

Line::Line(const Line& line) {
	if (this != &line) {
		for (auto& shape : line.shapes) {
			this->shapes.push_back(shape);
		}
		this->id = line.id;
	}
}

Line& Line::operator=(const Line& line) {
	if (this != &line) {
		for (auto& shape : line.shapes) {
			Shape newShape(shape.type, shape.start, shape.center, shape.end);
			this->shapes.push_back(newShape);
		}
		this->id = line.id;
	}
	return *this;
}

bool Line::Select(const wxPoint& point) {
	for (auto& shape : shapes) {
		if (shape.Contains(point)) {
			return true;
		}
	}
	return false;
}