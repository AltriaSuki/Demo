#include"draw.h"
#include<wx/dcbuffer.h>
#include<fstream>
#include"nlohmann/json.hpp"
#include"element.h"
#include"Line.h"
using json = nlohmann::json;
extern int currentToolId;
extern bool DrawMode;
bool isDragging = false;
wxPoint dragStartPos;
wxColour color = *wxBLUE;
int currentElementId = -1;
int currentElementTypeId =-1;
int currentLineId = -1;
bool isStartFromElement=false;
wxPoint currentOutputPoint;
wxPoint currentInputPoint;
bool isPointInCircle(wxPoint p, wxPoint center, int radius) {
	return (p.x - center.x) * (p.x - center.x) + (p.y - center.y) * (p.y - center.y) <= radius * radius;
}
Draw::Draw(wxWindow *parent) :wxPanel(parent) {
	lineId = 0;
	for (int i = 0; i < 100; i++)
		id[i] = 0;
	LoadFromJSON("and_gate.json");
	/*LoadFromJSON("or_gate.json");
	LoadFromJSON("Nand_gate.json");*/
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	Bind(wxEVT_PAINT, &Draw::OnPaint, this);
	Bind(wxEVT_LEFT_DOWN, &Draw::OnMouseDown, this);
	Bind(wxEVT_MOTION, &Draw::OnMotion, this);
	Bind(wxEVT_LEFT_UP, &Draw::OnMouseUp, this);
	Bind(wxEVT_SIZE, &Draw::OnResize, this);
	Bind(wxEVT_RIGHT_DOWN, &Draw::OnRightClick, this);
}

void Draw::OnResize(wxSizeEvent& event) {

	if (GetClientSize().GetWidth() > 0 && GetClientSize().GetHeight() > 0) {
		wxBitmap newBitmap(GetClientSize());
		wxMemoryDC memDC(newBitmap);
		memDC.Clear();
		if (bitMap.IsOk()) {

			memDC.DrawBitmap(bitMap, 0, 0);
		}
		bitMap = newBitmap;
	}
	Refresh();  
}

void Draw::OnRightClick(wxMouseEvent& event) {
	wxMenu menu;
	menu.Append(1000, "Delete");
	ElementSelect(event);
	LineSelect(event);
	if (currentElementId != -1) {
		PopupMenu(&menu, event.GetPosition());
	}
	if (currentLineId != -1) {
		PopupMenu(&menu, event.GetPosition());
	}
	
	Bind(wxEVT_MENU, &Draw::OnMenuSelection, this, 1000);
}

void Draw::OnMenuSelection(wxCommandEvent& event) {
	if (event.GetId() == 1000) {
		if (currentElementId != -1) {
			for (auto it = elements.begin(); it != elements.end(); ++it) {
				if (it->id == currentElementId) {
					elements.erase(it);
					currentElementId = -1;
					break;
				}
			}
		}
		if (currentLineId != -1) {
			
			for (auto it = lines.begin(); it != lines.end(); ++it) {
				if (it->id == currentLineId) {
					lines.erase(it);
					currentLineId = -1;
					break;
				}
			}
		}
	}
	
	Refresh();
}
void Draw::OnPaint(wxPaintEvent& event) {
	wxMemoryDC memDC(bitMap);

	memDC.DrawBitmap(bitMap, 0, 0);
}
void Draw::OnMouseDown(wxMouseEvent& event) {
	startpoint = event.GetPosition();
	endpoint = startpoint;

	if (DrawMode) {
		for (auto element : elements) {
			for (auto inputpoint : element.inputPoint)
				if (isPointInCircle(startpoint,inputpoint,5)) {
					isDrawing = true;
					startpoint = inputpoint;
					LineSelect(event);
					isStartFromElement = true;
					break;
				}
			if (isDrawing)break;
			for (auto outputpoint : element.outputPoint)
				if (isPointInCircle(startpoint, outputpoint, 5)) {
					isDrawing = true;
					startpoint = outputpoint;
					isStartFromElement = true;
					LineSelect(event);
					break;
				}
		}
		if (!isDrawing) {
			isStartFromElement = false;
			for (auto line : lines) {
				for (auto shape : line.shapes) {
					if (shape.Contains(startpoint)) {
						isDrawing = true;
						if (shape.start.y == shape.end.y) {
							startpoint.y = shape.start.y;
						}
						else if (shape.start.x == shape.end.x) {
							startpoint.x = shape.start.x;
						}
						//startpoint.x = shape.start.x;
						break;
					}
				}
				if (isDrawing)break;
			}
		}
		
	}
	else {
		ElementSelect(event);
	}
	
}
void Draw::OnMotion(wxMouseEvent& event) {
	wxPoint currentPoint = event.GetPosition();
	endpoint = currentPoint;
	wxPoint offset;
	wxClientDC dc(this);
	dc.DrawBitmap(bitMap, 0, 0);
	wxPen pen(color, 2);
	dc.SetPen(pen);
	if (isDrawing) {

		wxPoint MiddlePoint;
		if (isStartFromElement)MiddlePoint = wxPoint(currentPoint.x, startpoint.y);
		else {
			MiddlePoint = wxPoint(startpoint.x, currentPoint.y);
		}
		

		dc.DrawLine(startpoint, MiddlePoint);
		dc.DrawLine(MiddlePoint, currentPoint);

	}
	else if (!DrawMode) {
		offset = currentPoint - dragStartPos;
		dragStartPos = currentPoint;
			
		Refresh();
	}


	for (auto line : lines) {
		for (auto& shape : line.shapes) {
			shape.Draw(dc);
		}
	}
	
	for (auto& element : elements) {
		if (element.id == currentElementId) {
			for (auto &outputpoint : element.outputPoint) {
				outputpoint.x += offset.x;
				outputpoint.y += offset.y;


			}
			for (auto &inputpoint : element.inputPoint) {
				inputpoint.x += offset.x;
				inputpoint.y += offset.y;
			}
			for (auto& shape : element.shapes) {
				shape.Move(offset.x, offset.y);
				shape.Draw(dc);
			}
		}
		else {
			for (auto& shape : element.shapes) {
				shape.Draw(dc);
			}
		}
	}


}
void Draw::OnMouseUp(wxMouseEvent& event) {
	wxMemoryDC memDC(bitMap);
	memDC.Clear();
	wxPen pen(color, 2);
	memDC.SetPen(pen);
	if (DrawMode&&isDrawing==true) {
		isDrawing = false;
		wxPoint MiddlePoint;
		if (isStartFromElement)MiddlePoint = wxPoint(endpoint.x, startpoint.y);
		else {
			MiddlePoint = wxPoint(startpoint.x, endpoint.y);
		}
		Line NewLine;
		NewLine.id = lineId++;
		NewLine.shapes.push_back(Shape("line", startpoint, wxPoint((startpoint.x + MiddlePoint.x) / 2,
			(startpoint.y + MiddlePoint.y) / 2), MiddlePoint));
		NewLine.shapes.push_back(Shape("line", MiddlePoint, wxPoint((endpoint.x + MiddlePoint.x) / 2,
			(endpoint.y + MiddlePoint.y) / 2), endpoint));
		lines.push_back(NewLine);



		
	}
	else {

		currentElementId = -1;
		Refresh();
		

	}
}

void Draw::ElementSelect(wxMouseEvent& event) {
	wxPoint p = event.GetPosition();
	currentElementId = -1;

		for (auto& element : elements) {
			if (element.Select(p)) {
				element.isSelect = true;
				currentElementId = element.id;
				currentElementTypeId = element.type;
				break;
			}
		}
		Refresh();

}

void Draw::LineSelect(wxMouseEvent& event) {
	wxPoint p = event.GetPosition();
	currentLineId = -1;
	for (auto& line : lines) {
		if (line.Select(p)) {
			currentLineId = line.id;
			break;
		}
	}
}
void Draw::LoadFromJSON(const std::string& filename) {
	std::ifstream file(filename);
	int key=0;
	if (filename == "and_gate.json") {
		key = 0;
	}
	else if (filename == "or_gate.json") {
		key = 1;
	}
	else if (filename == "Nand_gate.json") {
		key = 2;
	}
	if (file.is_open()) {
		json data;
		file >> data;
		file.close();
		int count = 0;
		for (const auto& shape : data["shapes"]) {
			const std::string& type = shape["type"];
			wxPoint start(shape["start"][0], shape["start"][1]);
			wxPoint end(shape["end"][0], shape["end"][1]);
			wxPoint center((start.x + end.x) / 2, (start.y + end.y) / 2);
			switch (key) {
			case 0:
				AndGate.shapes.push_back(Shape(type, start, center, end));
				break;
			case 1:
				OrGate.shapes.push_back(Shape(type, start, center, end));
				break;
			case 2:
				NandGate.shapes.push_back(Shape(type, start, center, end));
				break;
			}
		}
	}
	else {
		wxMessageBox("Failed to open file", "Error", wxICON_ERROR);
	}
	AndGate.outputPoint.push_back(wxPoint(40, 30));
}
void Draw::CreateElement() {
	wxMemoryDC memDC(bitMap);
	wxPen pen(color, 1);
	memDC.SetPen(pen);
	Element NewElement;
	switch (currentToolId) {
	case 0:
		NewElement = AndGate;
		NewElement.id = id[0]++;
		elements.push_back(NewElement);
		break;
	case 1:
		NewElement = OrGate;
		NewElement.id = id[1]++;
		elements.push_back(NewElement);
		break;
	case 2:
		NewElement = NandGate;
		NewElement.id = id[2]++;
		elements.push_back(NewElement);
		break;
	}
	wxString message = wxString::Format("id: %d", NewElement.id);
	wxMessageBox(message, "Success", wxICON_INFORMATION);
	Refresh();
	
}