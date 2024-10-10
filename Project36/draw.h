#pragma once
#include<wx/wx.h>
class Draw : public wxPanel {
public :
	Draw(wxWindow *parent);
	void OnPaint(wxPaintEvent& event);
	void OnMouseDown(wxMouseEvent& event);
	void OnMouseUp(wxMouseEvent& event);
	void OnMotion(wxMouseEvent& event);
private:
	bool isDrawing = false;
	wxPoint startpoint,endpoint;
	wxBitmap bitMap;

};