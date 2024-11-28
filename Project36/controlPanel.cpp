#include <wx/treectrl.h>
#include<wx/wx.h>
#include "controlPanel.h"
#include <wx/sizer.h>
#include <wx/Image.h>
#include"element.h"
#include"myFrame.h"

control::control(wxWindow* parent) :wxPanel(parent) {
	MyTreeCtrl = new wxTreeCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT);
	Fillimage();
	FillTree();
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(MyTreeCtrl, 1, wxEXPAND | wxALL, 5);
	this->SetSizer(sizer);
	Bind(wxEVT_TREE_ITEM_ACTIVATED, &control::OnTreeItemSelected, this);

}

void control::FillTree()//填充目录树
{
	wxTreeItemId root1 = MyTreeCtrl->AddRoot("current file");
	wxTreeItemId dir1 = MyTreeCtrl->AppendItem(root1, "element file");
	wxTreeItemId dir2 = MyTreeCtrl->AppendItem(dir1, "and gate");
	int id1 = 0;
	MyTreeCtrl->SetItemData(dir2, new MyTreeItemData(0));


}

void control::Fillimage()//填充图标
{
	wxImage::AddHandler(new wxPNGHandler);
	wxImageList* imageList = new wxImageList(16, 16);
	wxBitmap bitmap(wxT("E:\\VS\\WxDemo\\Project36\\Demo\\Project36\\and_gate2.png"), wxBITMAP_TYPE_PNG);
	imageList->Add(bitmap);
	MyTreeCtrl->SetImageList(imageList);
}





void control::OnTreeItemSelected(wxTreeEvent& event)
{
	wxTreeItemId selectedItem = event.GetItem();//获取选择的子项树
	MyTreeItemData* data = static_cast<MyTreeItemData*>(MyTreeCtrl->GetItemData(selectedItem));
    int toolid = data->GetID();
	
	wxWindow* SPanel = dynamic_cast<wxWindow*>(GetParent());
	if (SPanel) {
		MyFrame* myFrame = dynamic_cast<MyFrame*>(SPanel->GetParent());
		if (myFrame) {
			myFrame->onTreeClick(toolid); // 调用 MyFrame 的功能函数
		}
	}
	event.Skip();

}

