#pragma once

inline float Height(RECT x) { return  x.bottom-x.top; }

inline RECT RectMake(int x, int y, int w, int h) {
	return{ x,y,x + w,y + h };
}

inline RECT RectCenter(int x, int y, int w, int h) {

	return{ x - w / 2, y - h / 2, x + w / 2, y + h / 2 };
}

inline void RRect(HDC h, RECT rc) {

	Rectangle(h, rc.left, rc.top, rc.right, rc.bottom);
}

inline void REllipse(HDC h, RECT rc) {

	Ellipse(h, rc.left, rc.top, rc.right, rc.bottom);
}

inline void REllipse(HDC h, int x, int y, int r) {

	Ellipse(h, x - r, y - r, x + r, y + r);
}

inline void RLine(HDC h, int x, int y, int ex, int ey) {

	MoveToEx(h, x, y, NULL);
	LineTo(h, ex, ey);
}



