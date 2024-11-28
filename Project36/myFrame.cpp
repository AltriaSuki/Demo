#include"myFrame.h"
#include"draw.h"
#include"Control.h"
#include"element.h"
#include <wx/splitter.h>
#include"nlohmann/json.hpp"
#include<vector>
using json = nlohmann::json;
int currentToolId = 1000;
bool DrawMode = true;
MyFrame::MyFrame(const wxString& title) :wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1200, 800)) {
	menuBar = new wxMenuBar;
	file = new wxMenu;
	file->Append(wxID_NEW, wxT("&News"));
	file->Append(wxID_OPEN, wxT("&Open"));
	file->Append(wxID_SAVE, wxT("&Save"));
	file->AppendSeparator();
	imp = new wxMenu;
	imp->Append(wxID_ANY, wxT("import from 1"));
	imp->Append(wxID_ANY, wxT("import from 2"));
	file->AppendSubMenu(imp, wxT("import"));
	file->Append(wxID_CLOSE, wxT("&Quit"));
	file->Append(wxID_ABOUT, "About", "Show something about");
	menuBar->Append(file, wxT("&File"));
	SetMenuBar(menuBar);
	CreateStatusBar(2);
	SetStatusText(wxT("welcome to wxWidgets!"));
	
	Centre();

	splitter = new wxSplitterWindow(this);
	controlPanel = new control(splitter);
	drawPanel = new Draw(splitter);
	splitter->SplitVertically(controlPanel, drawPanel,200);
	
	//工具栏部分
	     wxImage::AddHandler(new wxPNGHandler);
        ////wxBitmap exit(_T("copy.png"), wxBITMAP_TYPE_PNG);
        //wxToolBar* toolbar = CreateToolBar();
        //toolbar->AddTool(wxID_EXIT, _T("Exit application"), exit);
        //toolbar->Realize();
        //Connect(wxID_EXIT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MyFrame::onQuit));
	wxToolBar* toolBar = CreateToolBar();
	wxBitmap bitmap(wxT("E:\\VS\\WxDemo\\Project36\\Demo\\Project36\\and_gate2.png"), wxBITMAP_TYPE_PNG);
	toolBar->AddTool(0, "And Gate", bitmap);
	toolBar->AddTool(1, "Change Mode", bitmap);
	toolBar->Realize();
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MyFrame::onQuit, this, wxID_CLOSE);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MyFrame::onAbout, this, wxID_ABOUT);
	Bind(wxEVT_SIZE, &MyFrame::OnResize, this);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MyFrame::OnOpenFileClick, this, wxID_OPEN);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MyFrame::OnNewClick, this, wxID_NEW);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MyFrame::OnSaveClick, this, wxID_SAVE);
	//Bind(wxEVT_TOOL, &MyFrame::DrawAll, this);
	Bind(wxEVT_TOOL, &MyFrame::OnToolClicked, this);
    Centre();
}
void MyFrame::OnResize(wxSizeEvent& event) {
	Layout();
	event.Skip();
}
void MyFrame::onQuit(wxCommandEvent&event) {
	Close(true);
	event.Skip();
}
void MyFrame::onAbout(wxCommandEvent& WXUNUSED(event)) {
	wxMessageBox(wxT("This is about something"), wxT("ABOUT"), wxOK | wxICON_INFORMATION);
}

void MyFrame::OnNewClick(wxCommandEvent& event)//点击new
 {
     auto* frame = new MyFrame(wxT("Hello wxWidgets!"));
     frame->Show(true);
 }

    //点击open打开文件
 void MyFrame::OnOpenFileClick(wxCommandEvent& event)
         {
     wxTextCtrl* text1=NULL;
             wxFileDialog dlg(this, wxT("打开logism project"), wxT(""), wxT(""),
                                  wxT(".circ(*.circ)|*.circ"),
                                  wxFD_OPEN | wxFD_FILE_MUST_EXIST);
          if (dlg.ShowModal() == wxID_CANCEL)
                  return;
          text1->LoadFile(dlg.GetPath());
       
           }
 //点击save
 void MyFrame::OnSaveClick(wxCommandEvent& event)
 {

 }

 void MyFrame::onTreeClick(int id)
 {
	 currentToolId = id;
	 //drawPanel->DrawAll();//应该为createSomeKindOfElement
	 drawPanel->CreateElement();

 }

 void MyFrame::OnToolClicked(wxCommandEvent& event) {

	 int toolId = event.GetId();
	 currentToolId = toolId;
	 if (toolId <=10&&toolId>=0) {
		 if (toolId == 1) {
			 DrawMode = !DrawMode;
			 if (DrawMode == 1) {
				 wxMessageBox(wxT("Now is Draw Mode"), wxT("Mode"), wxOK | wxICON_INFORMATION);
				 Refresh();
			 }
			 else {
				 wxMessageBox(wxT("Now is Select Mode"), wxT("Mode"), wxOK | wxICON_INFORMATION);
			 }
			 return;
		 }
		 drawPanel->CreateElement();
		 
	 }
	 //drawPanel->DrawAll();//应该为createSomeKindOfElement
	 event.Skip();
 }
 //void MyFrame::DrawAll(wxCommandEvent&event) {
	// wxMemoryDC memDC(drawPanel->bitMap);
	// wxPen pen(*wxGREEN, 2);
	// memDC.SetPen(pen);
	// switch (currentToolId) {
	// case 0:
	//	 for (auto& shape : AndGate.shapes) {
	//		 shape.Draw(memDC);
	//	 }
	//	 break;
	// }
	// currentToolId = 5;
	// event.Skip();
 //}