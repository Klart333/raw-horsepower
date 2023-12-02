#pragma once
#include <cmath>

struct Vector2
{
    float x;
    float y;

    Vector2()
    {
        x = 0;
        y = 0;
    }
    
    Vector2(const float ex, const float why)
    {
        x = ex;
        y = why;
    }

    Vector2 operator*(const float num) const
    {
        Vector2 old = *this;
        old.x *= num;
        old.y *= num;
        return old;
    }

    Vector2 operator+(const Vector2 vec) const
    {
        Vector2 old = *this;
        old.x += vec.x;
        old.y += vec.y;
        return old;
    }

    Vector2 operator-(const Vector2 vec) const
    {
        Vector2 old = *this;
        old.x -= vec.x;
        old.y -= vec.y;
        return old;
    }

    [[nodiscard]]
    float Magnitude() const
    {
        const float length = sqrt(x * x + y * y);
        return length;
    }

    Vector2 Normalize()
    {
        const float mag = Magnitude();
        if (mag <= 0)
        {
            return *this;
        }
        this->y = y / mag;
        this->x = x / mag;
        return *this;
    }

    Vector2 Round()
    {
        this->y = round(y);
        this->x = round(x);
        return *this;
    }
};
