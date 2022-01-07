#include "BulletBonus.h"
#include <Windows.h>
#include <iostream>
extern HDC hdc;
BulletBonus::BulletBonus(int InitX, int InitY) : Bonus(InitX, InitY) {
}

BulletBonus::~BulletBonus() {
}

HPEN BulletBonus::SetColor() {
    return CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
}
