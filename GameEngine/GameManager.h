#pragma once

class GameObject;

class GameManager
{
    int capacity;
    
public:
    int count;
    GameObject** GameObjects;
    
    GameManager();
    ~GameManager();
    void AddGameObject(GameObject* object); 
};
