#pragma once
#include<wx/wx.h>
#include<list>
#include"element.h"
#include"Line.h"
class Draw : public wxPanel {
public :
	Draw(wxWindow *parent);
	void OnPaint(wxPaintEvent& event);
	void OnMouseDown(wxMouseEvent& event);
	void OnMouseUp(wxMouseEvent& event);
	void OnMotion(wxMouseEvent& event);
	void OnResize(wxSizeEvent& event);
	void LoadFromJSON(const std::string& filename);
	bool isSelect(wxMouseEvent&event);
	std::list<Element> elements;
	std::list<Line> lines;
	Element AndGate;
	Element OrGate;
	Element NandGate;
	void DrawAll();
	void ElementSelect(wxMouseEvent& event);
	void LineSelect(wxMouseEvent& event);
	void CreateElement();
	void OnRightClick(wxMouseEvent& event);
	void OnMenuSelection(wxCommandEvent& event);
private:
	bool isDrawing = false;
	wxPoint startpoint,endpoint;
	wxBitmap bitMap;
	wxBitmap LinerMap;
	int id[100];
	int lineId;
};