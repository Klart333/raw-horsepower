#pragma once
#include <map>
#include <SDL_render.h>
#include "IImageLoader.h"


class ISDLImageLoader : public IImageLoader
{
    SDL_Renderer* renderer;
    
public:
    ISDLImageLoader(SDL_Renderer* renderer);

    SDL_Texture* LoadImage(const char* path) override;
    
private:
    static std::map<const char*, SDL_Texture*> LoadedTextures;
};
