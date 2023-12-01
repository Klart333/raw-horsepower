#include "Image.h"

#include "IImageLoader.h"

Image::Image()
{
    texture = nullptr;
    renderOrder = 0;
}

Image::Image(const char* path, IImageLoader* image_loader, int rendOrder)
{
    texture = image_loader->LoadImage(path);
    renderOrder = rendOrder;
}

SDL_Texture* Image::getTexture() const
{
    return texture;
}
