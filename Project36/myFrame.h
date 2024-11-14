#pragma once
#include<wx/wx.h>
#include"draw.h"
#include <wx/splitter.h>
#include<fstream>
#include<list>
#include"element.h"
#include"controlPanel.h"
class MyFrame :public wxFrame {
public:
	MyFrame(const wxString& title);
	void onQuit(wxCommandEvent& event);
	void onAbout(wxCommandEvent& event);
	wxMenuBar* menuBar;
	wxMenu* file;
	wxMenu* imp;
	Element AndGate;
	void OnResize(wxSizeEvent& event);
	void DrawAll(wxCommandEvent&event);
	void OnOpenFileClick(wxCommandEvent& event);
	void OnNewClick(wxCommandEvent& event);
	void OnSaveClick(wxCommandEvent& enent);
	void OnToolClicked(wxCommandEvent& event);
	void onTreeClick(int id);

private:
	//int currentToolId = 1000;
	wxSplitterWindow* splitter;
	control* controlPanel;
	Draw* drawPanel;
	wxPaintDC* dc;
};