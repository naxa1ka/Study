#pragma once

#include "Point.h"
#include "Entity.h"
#include "Direction.h"
#include "IDyeable.h"

class Bullet : public Entity, public IDyeable { //класс для пули
protected:
    DIRECTION direction; //направление движения пули
public:
    Bullet(int InitX, int InitY, DIRECTION direction); //конструктор

    ~Bullet(); //деструктор

    void virtual Show() override; 

    void virtual Update() override;

    void virtual OnCollision(Entity* entity) override;

    virtual HPEN SetColor() override;
};

