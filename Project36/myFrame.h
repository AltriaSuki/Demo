#pragma once
#include<wx/wx.h>
#include"draw.h"
#include <wx/splitter.h>
class MyFrame :public wxFrame {
public:
	MyFrame(const wxString& title);
	void onQuit(wxCommandEvent& event);
	void onAbout(wxCommandEvent& event);
	wxMenuBar* menuBar;
	wxMenu* file;
	wxMenu* imp;
	void OnResize(wxSizeEvent& event);
	void OnOpenFileClick(wxCommandEvent& event);
	void OnNewClick(wxCommandEvent& event);
	void OnSaveClick(wxCommandEvent& enent);
	void AddButton(const wxString& label);
	void OnMyItemClick(wxCommandEvent& event);
private:
	wxSplitterWindow* splitter;
	wxPanel* controlPanel;
	Draw* drawPanel;
};