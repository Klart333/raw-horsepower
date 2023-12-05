#pragma once

struct Vector2Int
{
    Vector2Int()
    {
        X = -1;
        Y = -1;
    }
    int X;
    int Y;
    Vector2Int(int x, int y)
    {
        X = x;
        Y = y;
    }
};
