#pragma once
#include "GameObject.h"
#include "JohnsArray.h"

class CollisionSystem
{
public:
    static void Update(const JohnsArray<GameObject>* gameObjects);
};
