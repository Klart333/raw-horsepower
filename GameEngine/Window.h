#pragma once
#include "Image.h"
#include "SDL.h"

class GameObject;
class IDisplayWindow;
class IImageLoader;

class Window
{
    //The window we'll be rendering to
    IDisplayWindow* window{};
    
    //The surface contained by the window
    SDL_Surface* screenSurface{};
    
    //Whether Window Startup was successful
    bool success; // Why would I care about this, if it failed it failed there's nothing to do. 
    
    // dependency to the ImageLoader
    IImageLoader* imageLoader;
    
public:
    Window(IDisplayWindow* displayWindow, IImageLoader* imageLoader);
    ~Window();
    bool wasSuccessful() const { return success; }
    void render(GameObject* gameObject);
    void clear() const;
    void present();
};



