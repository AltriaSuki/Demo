#pragma once
#include<wx/wx.h>
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
};