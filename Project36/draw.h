#pragma once
#include<wx/wx.h>
#include<list>
#include"element.h"
class Draw : public wxPanel {
public :
	Draw(wxWindow *parent);
	void OnPaint(wxPaintEvent& event);
	void OnMouseDown(wxMouseEvent& event);
	void OnMouseUp(wxMouseEvent& event);
	void OnMotion(wxMouseEvent& event);
	void OnResize(wxSizeEvent& event);
	void LoadFromJSON(const std::string& filename);
	Element AndGate;
	Element OrGate;
	Element NandGate;
	void DrawAll();
	void ElementSelect(wxMouseEvent& event);
private:
	bool isDrawing = false;
	wxPoint startpoint,endpoint;
	wxBitmap bitMap;

};