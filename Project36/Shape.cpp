#include"Shape.h"
void Shape::Draw(wxDC& dc) {
	if (type == "line") {
		dc.DrawLine(start, end);
	}
	else if (type == "arc") {
		dc.DrawArc(start, end, center);
	}
}
bool Shape::Contains(const wxPoint& p) {
	if (type == "line") {
		wxRect rect(std::min(start.x, end.x) - 5, std::min(start.y, end.y) - 5,
			std::abs(start.x - end.x) + 10, std::abs(start.y - end.y) + 10);
		return rect.Contains(p);
	}
	else if (type == "arc") {
		wxRect rect(std::min(start.x, end.x) - 5, std::min(start.y, end.y) - 5,
			std::abs(start.x - end.x) + 10, std::abs(start.y - end.y) + 10);
		return rect.Contains(p);
	}
	return false;
}