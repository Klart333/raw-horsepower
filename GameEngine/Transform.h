#pragma once
#include "Vector2.h"

struct SDL_Rect;

class Transform
{
    SDL_Rect* rect;
    
public:
    Transform(int pos_x, int pos_y, int width, int height);

    float PosX;
    float PosY;
    int Width;
    int Height;
    int Rotation = 0;

    void Move(float x, float y);
    void Move(Vector2 vector);
    void SetPosition(float x, float y);
    void SetPosition(Vector2 pos);
    void SetScale(int width, int height);

    [[nodiscard]]
    SDL_Rect* getRect() const;
};
