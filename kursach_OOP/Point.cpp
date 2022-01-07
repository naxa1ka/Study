#include "Point.h"
#include <windows.h>

extern HDC hdc;

Point::Point(int InitX, int InitY) : Location(InitX, InitY) {
    Visible = false;
}

Point::~Point() {
}

bool Point::IsVisible() {
    return Visible;
};

void Point::MoveTo(int NewX, int NewY) {
    Hide();
    X = NewX;
    Y = NewY;
    Show();
};

void Point::Hide() {
    Visible = false;

    SetPixel(hdc, X, Y, RGB(0, 0, 255));
    SetPixel(hdc, X + 1, Y, RGB(0, 0, 255));
    SetPixel(hdc, X, Y + 1, RGB(0, 0, 255));
    SetPixel(hdc, X + 1, Y + 1, RGB(0, 0, 255));
}

void Point::Show() {
    Visible = true;

    SetPixel(hdc, X, Y, RGB(255, 0, 0));
    SetPixel(hdc, X + 1, Y, RGB(255, 0, 0));
    SetPixel(hdc, X, Y + 1, RGB(255, 0, 0));
    SetPixel(hdc, X + 1, Y + 1, RGB(255, 0, 0));
}


