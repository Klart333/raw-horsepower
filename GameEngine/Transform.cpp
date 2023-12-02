#include "Transform.h"

#include <SDL_rect.h>

#include "Vector2.h"

Transform::Transform(int pos_x, int pos_y, int width, int height): PosX(pos_x),
                                                                   PosY(pos_y),
                                                                   Width(width),
                                                                   Height(height)
{
    rect = new SDL_Rect{
        static_cast<int>(PosX),
        static_cast<int>(PosY),
        Width,
        Height,
    };
}

void Transform::Move(float x, float y)
{
    this->PosX += x;
    this->PosY += y;

    rect->x = static_cast<int>(PosX);
    rect->y = static_cast<int>(PosY);
}

void Transform::Move(Vector2 vector)
{
    this->PosX += vector.x;
    this->PosY += vector.y;

    rect->x = static_cast<int>(PosX);
    rect->y = static_cast<int>(PosY);
}

void Transform::SetPosition(float x, float y)
{
    this->PosX = x;
    this->PosY = y;

    rect->x = static_cast<int>(PosX);
    rect->y = static_cast<int>(PosY);
}

void Transform::SetPosition(Vector2 pos)
{
    this->PosX += pos.x;
    this->PosY += pos.y;

    rect->x = static_cast<int>(PosX);
    rect->y = static_cast<int>(PosY);
}

void Transform::SetScale(int width, int height)
{
    this->Width = width;
    this->Height = height;
    
    rect->w = Width;
    rect->h = Height;
}

SDL_Rect* Transform::getRect() const
{
    return rect;
}
