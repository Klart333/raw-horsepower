#pragma once

class Spawner;
class InputManager;
class GameManager;

class Dependencies
{
private:
    static Dependencies* _instance;
public:
    GameManager* GameManager;
    InputManager* InputManager;
    Spawner* Spawner;

    static Dependencies* instance(); 
};
