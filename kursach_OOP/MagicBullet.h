#pragma once

#include "Bullet.h"

class MagicBullet : public Bullet { //магическая пуля - наследник обычной пули
public:
    MagicBullet(int InitX, int InitY, DIRECTION direction);

    ~MagicBullet();

    virtual void Update() override;

    HPEN SetColor() override;
};