#pragma once

#include <map>
#include <stack>
#include "Entity.h"

class EntityHandler { 
    //класс в котором идет все управление сущностями
private:
    static int entityID; //статичное поле с уникальным id каждой сущности, увеличивается при каждом взятии
    static std::map<int, Entity*> entityMap; //хранилище обновляемых объектов
    static std::stack<int> toDelEntity; //для корректной работы удаления

    static bool WasCollision(Entity* one, Entity* two); //проверка столкновений

    static void DeleteEntities(); //удаление занесенных сущностей

    static void Update();

    static void CheckCollision();

public:
    static int GetEntityID();

    static void AddEntity(int id, Entity* entity);

    static void RemoveEntity(int id);

    static void UpdateAll();

};


