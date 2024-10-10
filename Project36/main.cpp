//#include"menu.h"
//#include"toolbar.h"
#include"main.h"
//#include"summaries.h"
//#include"draw.h"
#include"myFrame.h"
IMPLEMENT_APP(MyApp);
bool MyApp::OnInit() {
	//wxInitAllImageHandlers();
	/*Summaries* sample = new Summaries("sample");*/
	//ToolBar* toolbar = new ToolBar("ht bar");
	MyFrame* draw = new MyFrame("this is a drawing sample");
	draw->Show(true);
	return true;
}