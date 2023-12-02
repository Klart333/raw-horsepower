#include "Image.h"

#include "Dependencies.h"
#include "IImageLoader.h"
#include "Spawner.h"

Image::Image()
{
    texture = nullptr;
    renderOrder = 0;
}

Image::Image(const char* path, int rendOrder)
{
    texture = Dependencies::instance()->Spawner->image_loader->LoadImage(path);
    renderOrder = rendOrder;
}

SDL_Texture* Image::getTexture() const
{
    return texture;
}
