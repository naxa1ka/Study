#include "EntityHandler.h"
#include <iostream>
#include <queue>
#include <map>

int EntityHandler::GetEntityID() {
    return entityID++;
}

void EntityHandler::AddEntity(int id, Entity* entity) {
    entityMap.insert(std::make_pair(id, entity));
}

void EntityHandler::RemoveEntity(int id) {
    toDelEntity.push(id);
}

void EntityHandler::UpdateAll() {
    CheckCollision();
    DeleteEntities();
    Update();
}

void EntityHandler::Update() {
    for (auto& entity : entityMap) {
        entity.second->Update();
    }
}

void EntityHandler::CheckCollision() {
    for (auto& entitySource : entityMap) {
        for (auto& entityDestination : entityMap) {
            if (entitySource.first != entityDestination.first) {
                if (WasCollision(entitySource.second, entityDestination.second)) {
                    entitySource.second->OnCollision(entityDestination.second);
                }
            }
        }
    }
}

bool EntityHandler::WasCollision(Entity* one, Entity* two) {
    //TODO: check system on paper
    double oneX = (double)one->GetX() - (one->GetWidth());
    double twoX = (double)two->GetX() - (two->GetWidth());

    double oneY = (double)one->GetY() - (one->GetHeight());
    double twoY = (double)two->GetY() - (two->GetHeight());

    bool xcoll = oneX < twoX + two->GetWidth() && oneX + one->GetWidth() > twoX;
    bool ycoll = oneY < twoY + two->GetHeight() * 2 && oneY + one->GetHeight() * 2 > twoY;
    return xcoll and ycoll;
}

void EntityHandler::DeleteEntities() {
    while (!toDelEntity.empty()) {
        entityMap.erase(toDelEntity.top());
        toDelEntity.pop();
    }
}


int EntityHandler::entityID = 1;

std::map<int, Entity*> EntityHandler::entityMap;

std::stack<int> EntityHandler::toDelEntity;

