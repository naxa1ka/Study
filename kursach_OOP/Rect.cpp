#include "Rect.h"
#include <Windows.h>

extern HDC hdc;

Rect::Rect(int InitX, int InitY, int InitWidth, int InitHeight) : Point(InitX, InitY) {
    Width = InitWidth;
    Height = InitHeight;
}

Rect::Rect(int InitX, int InitY) : Point(InitX, InitY) {
}

Rect::~Rect() {
}

void Rect::Show() {
    Rectangle(hdc, X - Width, Y + Height, X + Width, Y - Height);
}

void Rect::Hide() {
    RECT r;
    r.left = X - Width - 3;
    r.top = Y + Height + 3;
    r.right = X + Width + 3;
    r.bottom = Y - Height - 3;

    HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
    FillRect(hdc, &r, brush);
    DeleteObject(brush);
}

int Rect::GetWidth() {
    return Width;
}

int Rect::GetHeight() {
    return Height;
}
