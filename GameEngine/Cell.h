#pragma once

constexpr int CellSize = 24;

class Image;
struct Cell
{
private:
   struct SDL_Rect* rect;
   
public:
    const Image* CoinImage;
    const Image* Image;
    
    bool Walkable;
    bool CointainsCoin;

    int X;
    int Y;

    Cell(): rect(nullptr), CoinImage(nullptr), Image(nullptr), CointainsCoin(false), X(0), Y(0)
    {
       Walkable = true;
   }

    Cell(const bool walkable, const bool coin, const class Image* img, const class Image* coin_image, const int x, const int y): rect(nullptr)
   {
        CointainsCoin = coin;
        Walkable = walkable;
        Image = img;
        CoinImage = coin_image;
        X = x;
        Y = y;
   }

   SDL_Rect* GetRect();
};
