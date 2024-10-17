#include"draw.h"
Draw::Draw(wxWindow *parent) :wxPanel(parent) {
	
	Bind(wxEVT_PAINT, &Draw::OnPaint, this);
	Bind(wxEVT_LEFT_DOWN, &Draw::OnMouseDown, this);
	Bind(wxEVT_MOTION, &Draw::OnMotion, this);
	Bind(wxEVT_LEFT_UP, &Draw::OnMouseUp, this);
	Bind(wxEVT_SIZE, &Draw::OnResize, this);
}
void Draw::OnResize(wxSizeEvent& event) {
	// �ڴ��ڴ�С�仯ʱ���´���λͼ����Ӧ�³ߴ�
	if (GetClientSize().GetWidth() > 0 && GetClientSize().GetHeight() > 0) {
		wxBitmap newBitmap(GetClientSize());
		wxMemoryDC memDC(newBitmap);
		memDC.Clear();
		if (bitMap.IsOk()) {
			// ���ɵĻ�ͼ���ݿ������µ�λͼ��
			memDC.DrawBitmap(bitMap, 0, 0);
		}
		bitMap = newBitmap;
	}
	Refresh();  
}
void Draw::OnPaint(wxPaintEvent& event) {
	wxPaintDC dc(this);
	if (!bitMap.IsOk()) {
		bitMap = wxBitmap(GetClientSize());//����һ���봰�ڴ�Сһ����λͼ
		wxMemoryDC memDC(bitMap);
		memDC.Clear();
	}
	dc.DrawBitmap(bitMap,0,0);//��λͼ���Ƶ����ڵģ�0��0��λ�á�
}
void Draw::OnMouseDown(wxMouseEvent& event) {
	isDrawing = true;
	startpoint = event.GetPosition();
	endpoint = startpoint;
}
void Draw::OnMotion(wxMouseEvent& event) {
	if (isDrawing) {
		wxClientDC dc(this);
		dc.DrawBitmap(bitMap, 0, 0);
		
		wxPen pen(*wxGREEN, 2);
		dc.SetPen(pen);
		wxPoint currentPoint = event.GetPosition();
		wxPoint MiddlePoint(currentPoint.x, startpoint.y);

		dc.DrawLine(startpoint, MiddlePoint);
		dc.DrawLine(MiddlePoint, currentPoint);
		endpoint = currentPoint;
	}
}
void Draw::OnMouseUp(wxMouseEvent& event) {
	isDrawing = false;
	wxMemoryDC memDC(bitMap);
	wxPen pen(*wxGREEN, 2);
	memDC.SetPen(pen);

	wxPoint MiddlePoint(endpoint.x, startpoint.y);
	memDC.DrawLine(startpoint, MiddlePoint);
	memDC.DrawLine(MiddlePoint, endpoint);
}