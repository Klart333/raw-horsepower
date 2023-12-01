#include "GameManager.h"
#include "GameObject.h"

GameManager::GameManager()
{
    GameObjects = new GameObject*[8];
    capacity = 8;
    count = 0;
}

GameManager::~GameManager()
{
    delete[] GameObjects; 
}

void GameManager::AddGameObject(GameObject* object)
{
    if (count >= capacity)
    {
        GameObject** temp = GameObjects;
        int oldCap = capacity;
        
        capacity *= 2;
        GameObjects = new GameObject*[capacity];

        for (int i = 0; i < oldCap; i++)
        {
            GameObjects[i] = temp[i];    
        }

        delete[] temp; // ???
    }
    
    GameObjects[count] = object;
    count++;
}
