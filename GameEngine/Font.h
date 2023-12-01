#pragma once
#include <SDL_ttf.h>

class Font
{
    TTF_Font* font;
public:
    Font(const char* fontPath);

    TTF_Font* getFont() const
    {
        return font;
    }
};
