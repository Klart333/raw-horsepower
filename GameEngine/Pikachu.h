#pragma once
#include "GameObject.h"
#include "Vector2.h"


class Pikachu : public GameObject
{
    Vector2 velocity;
public:
    Pikachu();
    void Update(const float deltaTime) override;
};
