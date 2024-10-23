#pragma once
#include<wx/wx.h>
class Element :public wxButton {
public:
	Element(wxWindow* parent,const wxString &title);
	void OnLeftDown(wxMouseEvent& event);
	void OnMotion(wxMouseEvent& event);
	void OnLeftUp(wxMouseEvent& event);
private:
	bool isDragging = false;
	wxPoint startpoint, endpoint;
};