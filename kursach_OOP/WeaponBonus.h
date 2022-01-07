#pragma once

#include <Windows.h>
#include "Bonus.h"

class WeaponBonus : public Bonus { //класс наследник бонуса - при подборе улучшает оружие
public:
    WeaponBonus(int InitX, int InitY); //конструктор 

    ~WeaponBonus(); //деструктор 

    HPEN SetColor() override; //изменяем цвет
};

