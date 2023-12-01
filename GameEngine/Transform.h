#pragma once
#include "Vector2.h"

class SDL_Rect;

class Transform
{
    SDL_Rect* rect;
    
public:
    Transform(int pos_x, int pos_y, int width, int height);

    float PosX;
    float PosY;
    int Width;
    int Height;

    void Move(float x, float y);
    void Move(Vector2 vector);
    void SetScale(int width, int height);

    SDL_Rect* getRect() const;
};
