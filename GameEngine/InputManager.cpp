#include "InputManager.h"

#include <SDL_events.h>

InputManager::InputManager()
{
    Quit = false;
    Horizontal = 0;
    Vertical = 0;
    OnMouseClicked = JohnsArray<FuncAndInstance>();
}

void InputManager::Update()
{
    SDL_Event e;
    	
    // loop through all pending events from Windows (OS)
    while (SDL_PollEvent(&e))
    {
        // check, if it's an event we want to react to:
        switch (e.type)
        {
            case SDL_QUIT:
            {
                Quit = true;
            } break;
            
            // This is an example on how to use input events:
            case SDL_KEYDOWN:
            {
                // input example: if left, then make pikachu move left
                if (e.key.keysym.sym == SDLK_LEFT)
                {
				
                }
                // if right, then make pikachu move right
                if (e.key.keysym.sym == SDLK_RIGHT)
                {
				
                }
            } break;
            case SDL_MOUSEBUTTONDOWN:
            {
                if (e.button.button == 1)
                {
                    for (int i = 0; i < OnMouseClicked.count; i++)
                    {
                        OnMouseClicked.Array[i]->func(OnMouseClicked.Array[i]->userData);
                    }
                }
            }
            default:
                break;
        }
    }

    Vertical = 0;
    Horizontal = 0;
    // This is an example for how to check, whether keys are currently pressed:
    const Uint8* keystate = SDL_GetKeyboardState(nullptr);
    if (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_W])
    {
        Vertical = -1;
    }
    if (keystate[SDL_SCANCODE_DOWN]|| keystate[SDL_SCANCODE_S])
    {
        Vertical = 1;
    }
    if (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D])
    {
        Horizontal = 1;
    }
    if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A])
    {
        Horizontal = -1;
    }
}

void InputManager::AddFunctionPointerToMouseButtonClicked(::CallBackFunction* callback, void* userData)
{
    OnMouseClicked.Add(new FuncAndInstance(callback, userData));
}

