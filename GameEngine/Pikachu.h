#pragma once

#include "GameObject.h"
#include "Vector2.h"

struct Cell;

class Pikachu : public GameObject
{
    Vector2 velocity;
    Cell* CurrentCell;
    
public:
    Pikachu();
    void UpdateCurrentCell();
    void Update(float deltaTime) override;

    void Shoot() const;

    static void CallbackFunction(void* userData)
    {
        static_cast<Pikachu*>(userData)->Shoot();
    }
};
