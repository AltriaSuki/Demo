#include"draw.h"
#include<wx/dcbuffer.h>
#include<fstream>
#include"nlohmann/json.hpp"
#include"element.h"
using json = nlohmann::json;
extern int currentToolId;
extern bool DrawMode;
bool isDragging = false;
wxPoint dragStartPos;
wxColour color = *wxBLUE;
int currentElementId = -1;
int currentElementTypeId =-1;
Draw::Draw(wxWindow *parent) :wxPanel(parent) {
	for (int i = 0; i < 100; i++)
		id[i] = 0;
	LoadFromJSON("and_gate.json");
	LoadFromJSON("or_gate.json");
	LoadFromJSON("Nand_gate.json");
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	Bind(wxEVT_PAINT, &Draw::OnPaint, this);
	Bind(wxEVT_LEFT_DOWN, &Draw::OnMouseDown, this);
	Bind(wxEVT_MOTION, &Draw::OnMotion, this);
	Bind(wxEVT_LEFT_UP, &Draw::OnMouseUp, this);
	Bind(wxEVT_SIZE, &Draw::OnResize, this);
}

void Draw::OnResize(wxSizeEvent& event) {
	// 在窗口大小变化时重新创建位图以适应新尺寸
	if (GetClientSize().GetWidth() > 0 && GetClientSize().GetHeight() > 0) {
		wxBitmap newBitmap(GetClientSize());
		wxMemoryDC memDC(newBitmap);
		memDC.Clear();
		if (bitMap.IsOk()) {
			// 将旧的绘图内容拷贝到新的位图中
			memDC.DrawBitmap(bitMap, 0, 0);
		}
		bitMap = newBitmap;
	}
	Refresh();  
}
void Draw::OnPaint(wxPaintEvent& event) {
	//wxAutoBufferedPaintDC dc(this);
	wxMemoryDC memDC(bitMap);
	//memDC.Clear();
	//if (currentElementId != -1) {
	//	for (auto& element : elements) {
	//		if (element.id == currentElementId) {
	//			for (auto& shape : element.shapes) {
	//				wxPen pen(*wxRED, 2);
	//				memDC.SetPen(pen);
	//				shape.Draw(memDC);
	//			}
	//		}
	//		else {
	//			for (auto& shape : element.shapes) {
	//				wxPen pen(color, 2);
	//				memDC.SetPen(pen);
	//				shape.Draw(memDC);
	//			}
	//		}
	//	}
	//}
	memDC.DrawBitmap(bitMap, 0, 0);
}
void Draw::OnMouseDown(wxMouseEvent& event) {
	startpoint = event.GetPosition();
	endpoint = startpoint;
	if (DrawMode) {
		isDrawing = true;
		
	}
	else {
		ElementSelect(event);
	}
	
}
void Draw::OnMotion(wxMouseEvent& event) {
	wxPoint currentPoint = event.GetPosition();
	endpoint = currentPoint;
	wxClientDC dc(this);
	dc.DrawBitmap(bitMap, 0, 0);
	wxPen pen(color, 1);
	dc.SetPen(pen);
	if (isDrawing) {
		wxPoint MiddlePoint(currentPoint.x, startpoint.y);

		dc.DrawLine(startpoint, MiddlePoint);
		dc.DrawLine(MiddlePoint, currentPoint);

	}
	else if (!DrawMode) {//有问题
		wxPoint offset = currentPoint - dragStartPos;
		dragStartPos = currentPoint;
		for (auto& shape : AndGate.shapes) {
			shape.Draw(dc);
		}
		if (currentElementId != -1) {
			for (auto& element : elements) {
				if (element.id == currentElementId) {
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
		
		Refresh();
	}
}
void Draw::OnMouseUp(wxMouseEvent& event) {
	wxMemoryDC memDC(bitMap);
	memDC.Clear();
	wxPen pen(color, 1);
	memDC.SetPen(pen);
	if (DrawMode) {
		isDrawing = false;


		wxPoint MiddlePoint(endpoint.x, startpoint.y);
		memDC.DrawLine(startpoint, MiddlePoint);
		memDC.DrawLine(MiddlePoint, endpoint);
	}
	else {
		for (auto& element : elements) {
			if (element.id == currentElementId) {
				for (auto& shape : element.shapes)
					shape.Draw(memDC);
				currentElementId = -1;
			}
			else {
				for (auto& shape : element.shapes)
					shape.Draw(memDC);
			}
		}
		Refresh();
		

	}
}

//void Draw::DrawAll() {
//	wxMemoryDC memDC(bitMap);
//	wxPen pen(color, 2);
//	memDC.SetPen(pen);
//	switch (currentToolId) {
//	case 0:
//		for (auto& shape : AndGate.shapes) {
//			shape.DrawInit(memDC);
//		}
//		break;
//	case 1:
//		for (auto& shape : OrGate.shapes) {
//			shape.DrawInit(memDC);
//		}
//		break;
//	case 2:
//		for (auto& shape : NandGate.shapes) {
//			shape.DrawInit(memDC);
//		}
//		break;
//	}
//	
//
//	Refresh(); 
//}
void Draw::ElementSelect(wxMouseEvent& event) {
	/*wxString message = wxString::Format("The number is: %d", currentElementId);
	wxMessageBox(message, "Success", wxICON_INFORMATION);*/
	wxPoint p = event.GetPosition();
	wxMemoryDC memDC(bitMap);
	memDC.Clear();
		for (auto& element : elements) {
			if (element.Select(p)) {
				element.isSelect = true;
				currentElementId = element.id;
				currentElementTypeId = element.type;
				break;
			}
		}
		Refresh();
		/*wxString newmessage = wxString::Format("The number is: %d", currentElementId);
		wxMessageBox(newmessage, "Success", wxICON_INFORMATION);*/
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
}
void Draw::CreateElement() {
	wxMemoryDC memDC(bitMap);
	wxPen pen(color, 1);
	memDC.SetPen(pen);
	/*switch (currentToolId) {
	case 0:
		for (auto& shape : AndGate.shapes) {
			shape.DrawInit(memDC);
		}
		break;
	case 1:
		for (auto& shape : OrGate.shapes) {
			shape.DrawInit(memDC);
		}
		break;
	case 2:
		for (auto& shape : NandGate.shapes) {
			shape.DrawInit(memDC);
		}
		break;
	}*/
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
	for (auto& shape : NewElement.shapes) {
		shape.DrawInit(memDC);
	}
	wxString message = wxString::Format("The number is: %d", NewElement.id);
	wxMessageBox(message, "Success", wxICON_INFORMATION);
	Refresh();
}