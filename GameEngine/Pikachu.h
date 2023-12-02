#pragma once

#include "GameObject.h"
#include "Vector2.h"


class Pikachu : public GameObject
{
    Vector2 velocity;
public:
    Pikachu();
    void Update(float deltaTime) override;

    void Shoot();

    static void CallbackFunction(void* userData)
    {
        static_cast<Pikachu*>(userData)->Shoot();
    }
};
