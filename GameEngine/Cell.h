#pragma once
#include <memory>
#include "Image.h"
constexpr int CellSize = 24;

class Image;
struct Cell
{
private:
   struct SDL_Rect* rect;
   
public:
    std::unique_ptr<Image> CoinImage;
    std::unique_ptr<Image> Image;
    
    bool Walkable;
    bool CointainsCoin;

    int X;
    int Y;

    Cell(): rect(nullptr), CoinImage(nullptr), Image(nullptr), CointainsCoin(false), X(0), Y(0)
    {
       Walkable = true;
   }

    Cell(const bool walkable, const bool coin, std::unique_ptr<class Image> img, std::unique_ptr<class Image> coin_image, const int x, const int y): rect(nullptr)
   {
        CointainsCoin = coin;
        Walkable = walkable;
        
        Image = std::move(img);
        CoinImage = std::move(coin_image);
        X = x;
        Y = y;
   }

   SDL_Rect* GetRect();
};
