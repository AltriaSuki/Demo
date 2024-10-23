#include"draw.h"
#include<wx/dcbuffer.h>
Draw::Draw(wxWindow *parent) :wxPanel(parent) {
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	Bind(wxEVT_PAINT, &Draw::OnPaint, this);
	Bind(wxEVT_LEFT_DOWN, &Draw::OnMouseDown, this);
	Bind(wxEVT_MOTION, &Draw::OnMotion, this);
	Bind(wxEVT_LEFT_UP, &Draw::OnMouseUp, this);
	Bind(wxEVT_SIZE, &Draw::OnResize, this);

}

void Draw::OnResize(wxSizeEvent& event) {
	// 在窗口大小变化时重新创建位图以适应新尺寸
	if (GetClientSize().GetWidth() > 0 && GetClientSize().GetHeight() > 0) {
		wxBitmap newBitmap(GetClientSize());
		wxMemoryDC memDC(newBitmap);
		memDC.Clear();
		if (bitMap.IsOk()) {
			// 将旧的绘图内容拷贝到新的位图中
			memDC.DrawBitmap(bitMap, 0, 0);
		}
		bitMap = newBitmap;
	}
	Refresh();  
}
void Draw::OnPaint(wxPaintEvent& event) {
	wxAutoBufferedPaintDC dc(this);
	dc.DrawBitmap(bitMap, 0, 0);
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