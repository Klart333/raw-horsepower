#include "Cell.h"
#include <SDL_rect.h>

SDL_Rect* Cell::GetRect()
{
    if (rect == nullptr)
    {
        rect = new SDL_Rect{
            X * CellSize,
            Y * CellSize,
            CellSize,
            CellSize,
        };
    }

    return rect;
}
