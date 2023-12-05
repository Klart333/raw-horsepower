#include "Image.h"

#include "Dependencies.h"
#include "IImageLoader.h"
#include "Spawner.h"

Image::Image()
{
    texture = nullptr;
    renderOrder = 0;
    AngleDeg = 0;
}

Image::Image(const char* path, const int rendOrder, const int angle)
{
    texture = Dependencies::instance()->Spawner->image_loader->LoadImage(path);
    renderOrder = rendOrder;
    AngleDeg = angle;
}

SDL_Texture* Image::getTexture() const
{
    return texture;
}
