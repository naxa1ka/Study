#include "WeaponBonus.h"

WeaponBonus::WeaponBonus(int InitX, int InitY) : Bonus(InitX, InitY) {
}

WeaponBonus::~WeaponBonus() {
}

HPEN WeaponBonus::SetColor() {
    return CreatePen(PS_SOLID, 2, RGB(0, 255, 255));
}
