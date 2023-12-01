#pragma once

class IImageLoader;

class Image
{
protected:
    struct SDL_Texture* texture;
public:
    int renderOrder;
    
    virtual ~Image() = default;
    Image();
    Image(const char* path, IImageLoader* image_loader, int rendOrder = 0);

    [[nodiscard]] SDL_Texture* getTexture() const; // i dont know what nodiscard is 
};
