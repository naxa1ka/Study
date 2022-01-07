#include "Bonus.h"
#include <Windows.h>
#include <typeinfo>
#include "GameWorld.h"
#include <iostream>
extern HDC hdc;

Bonus::Bonus(int InitX, int InitY) : Entity(InitX, InitY) {
    Width = 15;
    Height = 15;
}

Bonus::~Bonus() {
}

void Bonus::Show() {
    HPEN pen = SetColor();
    SelectObject(hdc, pen);
    Ellipse(hdc, X - Width, Y + Height, X + Width, Y - Height);
    Ellipse(hdc, X - Width / 2, Y + Height / 2, X + Width / 2, Y - Height / 2);
    DeleteObject(pen);
}

void Bonus::OnCollision(Entity* entity) {
    if (!strcmp(typeid(*entity).name(), "class Tank")) {
        Destroy();
    }
}

void Bonus::Update() {
    MoveTo(X - 15, Y);
    if (X < 0)
        Destroy();
}
