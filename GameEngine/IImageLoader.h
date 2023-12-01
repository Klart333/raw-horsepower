#pragma once
#include <SDL_render.h>

class IImageLoader
{
public:
    virtual ~IImageLoader() = default;
    IImageLoader() = default;
    
    virtual SDL_Texture* LoadImage(const char* path) = 0;
};
