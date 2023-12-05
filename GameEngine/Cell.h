#pragma once

constexpr int CellSize = 50;

class Image;
struct Cell
{
private:
   struct SDL_Rect* rect;
   
public:
    const Image* Image;
    bool Walkable;

    int X;
    int Y;

    Cell(): rect(nullptr), Image(nullptr), X(0), Y(0)
   {
       Walkable = true;
   }

    Cell(bool walkable, const class Image* img, int x, int y): rect(nullptr)
   {
       Walkable = walkable;
       Image = img;
       X = x;
       Y = y;
   }

   SDL_Rect* GetRect();
};
