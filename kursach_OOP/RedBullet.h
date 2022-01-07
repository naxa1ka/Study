#pragma once

#include "Bullet.h"

class RedBullet : public Bullet { //изменный цвет пули
public:
    RedBullet(int InitX, int InitY, DIRECTION direction);

    ~RedBullet();

    HPEN SetColor() override;
};

