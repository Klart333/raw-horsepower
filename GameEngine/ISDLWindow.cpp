#include "ISDLWindow.h"
#include <cstdio>
#include <SDL_image.h>
#include <SDL_ttf.h>

constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 1080;

ISDLWindow::ISDLWindow(int screenWidth, int screenHeight)
{
    renderer = nullptr;
    window = {};

    // initialize SDL_Image for image loading
    constexpr int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }

    // initialize SDL_ttf for font loading
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    }

    //Start up SDL and create window
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        //return -1;
    }

    // Create Window and Renderer
    SDL_CreateWindowAndRenderer(screenWidth, screenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, &window, &renderer);
    if (!window)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        //return -1;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

SDL_Window* ISDLWindow::get_window()
{
    return  window;
}

SDL_Renderer* ISDLWindow::get_Renderer()
{
    return renderer;
}
