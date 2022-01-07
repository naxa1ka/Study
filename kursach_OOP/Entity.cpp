#pragma once

#include "Entity.h"
#include "EntityHandler.h"
#include <iostream>

Entity::Entity(int InitX, int InitY) : Rect(InitX, InitY) {
    id = EntityHandler::GetEntityID();
    EntityHandler::AddEntity(id, this);
}

Entity::Entity(int InitX, int InitY, int Width, int Height) : Rect(InitX, InitY, Width, Height) {
    id = EntityHandler::GetEntityID();
    EntityHandler::AddEntity(id, this);
}

Entity::~Entity() {
    Destroy();
}

void Entity::Destroy() {
    EntityHandler::RemoveEntity(id);
    Hide();
}

