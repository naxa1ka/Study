#pragma once

#include "Rect.h"

class Entity : public Rect { 
    //класс сущности, используется для корректной работы всей системы:
    //Update - метод для обновления состояния объекта каждый кадр не прибегая вызовам из вне
    //OnCollision - система столкновения
private:
    int id; //уникальный индефикатор сущности
public:
    Entity(int initX, int initY); 
    Entity(int InitX, int InitY, int Width, int Height);
    //конструктор, в котором берется id из entityHandler
    //и добавляется в список объектов которые нужно обновлять
    virtual ~Entity();

    virtual void Update() = 0;

    virtual void OnCollision(Entity* entity) = 0;

    void Destroy(); //удаление объекта из системы
};

