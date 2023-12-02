#pragma once
#include "JohnsArray.h"

class GameObject;

class GameManager
{
    
public:
    JohnsArray<GameObject> GameObjects;
    
    GameManager();
    ~GameManager();
    void AddGameObject(GameObject* object); 
};

