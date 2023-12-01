#include "ISDLImageLoader.h"

#include <cstdio>
#include <SDL_image.h>
#include <SDL_surface.h>

ISDLImageLoader::ISDLImageLoader(SDL_Renderer* renderer)
{
    this->renderer = renderer; 
}

SDL_Texture* ISDLImageLoader::LoadImage(const char* path)
{
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == nullptr)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
        return nullptr;
    }
    else
    {
        //Convert surface to screen format
        SDL_Texture* pikachu = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (pikachu == nullptr)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
            return nullptr;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);

        return pikachu;
    }
}
