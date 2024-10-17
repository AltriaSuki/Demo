#include"myFrame.h"
#include"draw.h"
#include"MyCanvas.h"
#include <wx/splitter.h>
MyFrame::MyFrame(const wxString& title) :wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1200, 800)) {
	menuBar = new wxMenuBar;
	file = new wxMenu;
	file->Append(wxID_ANY, wxT("&News"));
	file->Append(wxID_ANY, wxT("&Open"));
	file->Append(wxID_ANY, wxT("&Save"));
	file->AppendSeparator();
	imp = new wxMenu;
	imp->Append(wxID_ANY, wxT("import from 1"));
	imp->Append(wxID_ANY, wxT("import from 2"));
	file->AppendSubMenu(imp, wxT("import"));
	file->Append(wxID_CLOSE, wxT("&Quit"));
	file->Append(wxID_ABOUT, "About", "Show something about");
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	
	menuBar->Append(file, wxT("&File"));
	SetMenuBar(menuBar);
	CreateStatusBar(2);//×´Ì¬À¸
	SetStatusText(wxT("welcome to wxWidgets!"));
	//Connect(wxID_CLOSE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SimpleMenu::onQuit));
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MyFrame::onQuit, this, wxID_CLOSE);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MyFrame::onAbout, this, wxID_ABOUT);
	Centre();
	wxSplitterWindow* splitter = new wxSplitterWindow(this);
	wxPanel* controlPanel = new wxPanel(splitter);
	Draw* drawPanel = new Draw(splitter);
	splitter->SplitVertically(controlPanel, drawPanel, 100);
	/*sizer->Add(controlPanel, 1, wxEXPAND | wxALL, 10);
	sizer->Add(drawPanel, 1, wxEXPAND | wxALL, 10);
	SetSizer(sizer);
	GetAutoLayout();*/
	Bind(wxEVT_SIZE, &MyFrame::OnResize, this);

}
void MyFrame::OnResize(wxSizeEvent& event) {
	Layout();
	event.Skip();
}
void MyFrame::onQuit(wxCommandEvent& WXUNUSED(event)) {
	Close(true);
}
void MyFrame::onAbout(wxCommandEvent& WXUNUSED(event)) {
	wxMessageBox(wxT("This is about something"), wxT("ABOUT"), wxOK | wxICON_INFORMATION);
}