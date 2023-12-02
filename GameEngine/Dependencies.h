#pragma once

class Spawner;
class InputManager;
class GameManager;
class Grid;

class Dependencies
{
private:
    static Dependencies* _instance;
public:
    GameManager* GameManager;
    InputManager* InputManager;
    Spawner* Spawner;
    Grid* Grid;

    static Dependencies* instance(); 
};
