#include "Dependencies.h"
#include "GameManager.h"
#include "Grid.h"
#include "InputManager.h"
#include "Spawner.h"

Dependencies* Dependencies::_instance;

Dependencies* Dependencies::instance()
{
    if (_instance == nullptr)
    {
        _instance = new Dependencies(); // Lazily create the instance
        _instance->GameManager = new class GameManager();
        _instance->InputManager = new class InputManager();
        _instance->Spawner = new class Spawner();
        _instance->Grid = new class Grid();
    }
    
    return _instance;
}
