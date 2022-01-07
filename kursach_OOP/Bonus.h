#pragma once

#include "Entity.h"
#include "IDyeable.h"

class Bonus : public Entity, public IDyeable { //абстрактный класс бонуса
public:
    Bonus(int InitX, int InitY); //конструктор

    ~Bonus(); //деструктор

    virtual void Show() override; //показ точки на экране

    virtual void Update() override; //передвижение точки

    virtual void OnCollision(Entity* entity) override; //столкновение

    virtual HPEN SetColor() override = 0;//изменение цвета
};

