#pragma once
#include<wx/wx.h>
#include <wx/sizer.h>
#include <wx/treectrl.h>

class control : public wxPanel {
public:
	control(wxWindow* parent);
		wxTreeCtrl* MyTreeCtrl;
		void FillTree();
		void Fillimage();
		void OnTreeItemSelected(wxTreeEvent & event);
private:
	
};
class MyTreeItemData : public wxTreeItemData {
public:
	MyTreeItemData(int id) : m_id(id) {}
	int GetID() const { return m_id; }

private:
	int m_id;
};