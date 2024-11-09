#include"Shape.h"
void Shape::Draw(wxDC& dc) {
	if (type == "line") {
		dc.DrawLine(currentStart,currentEnd);
	}
	else if (type == "arc") {
		dc.DrawArc(currentStart,currentEnd,currentCenter);
	}
}
void Shape::DrawInit(wxDC& dc) {
	if (type == "line") {
		dc.DrawLine(start, end);
	}
	else if (type == "arc") {
		dc.DrawArc(start, end, center);
	}
}
bool Shape::Contains(const wxPoint& p) {
	if (type == "line") {
		wxRect rect(std::min(currentStart.x, currentEnd.x) - 5, std::min(currentStart.y, currentEnd.y) - 5,
			std::abs(currentStart.x - currentEnd.x) + 10, std::abs(currentStart.y - currentEnd.y) + 10);
		return rect.Contains(p);
	}
	else if (type == "arc") {
		wxRect rect(std::min(currentStart.x, currentEnd.x) - 5, std::min(currentStart.y, currentEnd.y) - 5,
			std::abs(currentStart.x - currentEnd.x) + 10, std::abs(currentStart.y - currentEnd.y) + 10);
		return rect.Contains(p);
	}
	return false;
}
void Shape::Move(double offsetX, double offsetY) {
	currentStart.x += offsetX;
	currentStart.y += offsetY;
	currentEnd.x += offsetX;
	currentEnd.y += offsetY;
	currentCenter.x += offsetX;
	currentCenter.y += offsetY;
}