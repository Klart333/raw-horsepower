#include "GameManager.h"
#include "GameObject.h"

GameManager::GameManager()
{
    GameObjects = JohnsArray<GameObject>(8);
}

GameManager::~GameManager()
{
    delete[] GameObjects.Array;
}

void GameManager::AddGameObject(GameObject* object)
{
    GameObjects.Add(object);
}
