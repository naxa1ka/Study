#pragma once

#include <Windows.h>
#include "Bonus.h"

class BulletBonus : public Bonus { //класс наследник от бонуса - изменяет пулю игроку при подборе
public:
    BulletBonus(int InitX, int InitY);//конструктор

    ~BulletBonus(); //деструктор

    HPEN SetColor() override; //изменяем цвет
};

