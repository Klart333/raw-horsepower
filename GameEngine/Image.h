#pragma once

class IImageLoader;

class Image
{
protected:
    struct SDL_Texture* texture;
public:
    int renderOrder;
    int AngleDeg;
    
    virtual ~Image() = default;
    Image();
    Image(const char* path, int rendOrder = 0, int angle = 0);

    [[nodiscard]] SDL_Texture* getTexture() const; // i dont know what nodiscard is 
};
