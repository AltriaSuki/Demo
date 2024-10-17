#include"myFrame.h"
#include"draw.h"
#include <wx/splitter.h>
<<<<<<< HEAD
MyFrame::MyFrame(const wxString& title) :wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(600, 400)) {
	menuBar = new wxMenuBar;
	file = new wxMenu;
	file->Append(wxID_NEW, wxT("&News"));
	file->Append(wxID_OPEN, wxT("&Open"));
	file->Append(wxID_SAVE, wxT("&Save"));
=======
MyFrame::MyFrame(const wxString& title) :wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1200, 800)) {
	menuBar = new wxMenuBar;
	file = new wxMenu;
	file->Append(wxID_ANY, wxT("&News"));
	file->Append(wxID_ANY, wxT("&Open"));
	file->Append(wxID_ANY, wxT("&Save"));
>>>>>>> 3533732b3bedcc3179eeb22105687ceb00ab4dd7
	file->AppendSeparator();
	imp = new wxMenu;
	imp->Append(wxID_ANY, wxT("import from 1"));
	imp->Append(wxID_ANY, wxT("import from 2"));
	file->AppendSubMenu(imp, wxT("import"));
	file->Append(wxID_CLOSE, wxT("&Quit"));
	file->Append(wxID_ABOUT, "About", "Show something about");
<<<<<<< HEAD
	menuBar->Append(file, wxT("&File"));
	SetMenuBar(menuBar);
	CreateStatusBar(2);//״̬��
=======
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	
	menuBar->Append(file, wxT("&File"));
	SetMenuBar(menuBar);
	CreateStatusBar(2);//״̬��
>>>>>>> 3533732b3bedcc3179eeb22105687ceb00ab4dd7
	SetStatusText(wxT("welcome to wxWidgets!"));
	//Connect(wxID_CLOSE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SimpleMenu::onQuit));
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MyFrame::onQuit, this, wxID_CLOSE);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MyFrame::onAbout, this, wxID_ABOUT);
	Centre();
	wxSplitterWindow* splitter = new wxSplitterWindow(this);
	wxPanel* controlPanel = new wxPanel(splitter);
	Draw* drawPanel = new Draw(splitter);
	splitter->SplitVertically(controlPanel, drawPanel, 100);
<<<<<<< HEAD
	Bind(wxEVT_SIZE, &MyFrame::OnResize, this);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MyFrame::OnOpenFileClick, this, wxID_OPEN);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MyFrame::OnNewClick, this, wxID_NEW);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MyFrame::OnSaveClick, this, wxID_SAVE);
	//工具栏部分
	     wxImage::AddHandler(new wxPNGHandler);
        wxBitmap exit(_T("copy.png"), wxBITMAP_TYPE_PNG);
        wxToolBar* toolbar = CreateToolBar();
        toolbar->AddTool(wxID_EXIT, _T("Exit application"), exit);
        toolbar->Realize();
        Connect(wxID_EXIT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MyFrame::onQuit));
        Centre();

=======
	/*sizer->Add(controlPanel, 1, wxEXPAND | wxALL, 10);
	sizer->Add(drawPanel, 1, wxEXPAND | wxALL, 10);
	SetSizer(sizer);
	GetAutoLayout();*/
	Bind(wxEVT_SIZE, &MyFrame::OnResize, this);
>>>>>>> 3533732b3bedcc3179eeb22105687ceb00ab4dd7

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

void MyFrame::OnNewClick(wxCommandEvent& event)//点击new
 {
     auto* frame = new MyFrame(wxT("Hello wxWidgets!"));
     frame->Show(true);
 }

    //点击open打开文件
 void MyFrame::OnOpenFileClick(wxCommandEvent& event)
         {
     wxTextCtrl* text1=NULL;
             wxFileDialog dlg(this, wxT("打开C++源程序"), wxT(""), wxT(""),
                                  wxT("C++源程序(*.cpp)|*.cpp"),
                                  wxFD_OPEN | wxFD_FILE_MUST_EXIST);
          if (dlg.ShowModal() == wxID_CANCEL)
                  return;
          text1->LoadFile(dlg.GetPath());
       
           }
 //点击open
 void MyFrame::OnSaveClick(wxCommandEvent& enent)
 {

 }

