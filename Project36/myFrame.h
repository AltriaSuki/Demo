#pragma once
#include<wx/wx.h>
#include"draw.h"
#include <wx/splitter.h>
#include<fstream>
#include"element.h"
class MyFrame :public wxFrame {
public:
	MyFrame(const wxString& title);
	void onQuit(wxCommandEvent& event);
	void onAbout(wxCommandEvent& event);
	wxMenuBar* menuBar;
	wxMenu* file;
	wxMenu* imp;
	std::vector<Element> elements;
	void OnResize(wxSizeEvent& event);
	void OnOpenFileClick(wxCommandEvent& event);
	void OnNewClick(wxCommandEvent& event);
	void OnSaveClick(wxCommandEvent& enent);
	void LordFromJSON(const std::string& filename);
	void OnMyItemClick(wxCommandEvent& event);
private:
	wxSplitterWindow* splitter;
	wxPanel* controlPanel;
	Draw* drawPanel;
};