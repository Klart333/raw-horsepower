#pragma once

#include <SDL_render.h>
#include <SDL_video.h>
#include "IDisplayWindow.h"

class ISDLWindow : public IDisplayWindow
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    
public:
    ISDLWindow(int screenWidth, int screenHeight);
    
    SDL_Window* get_window() override;
    SDL_Renderer* get_Renderer() override;
};
