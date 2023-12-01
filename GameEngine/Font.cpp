#include "Font.h"

#include <SDL_ttf.h>

Font::Font(const char* fontPath)
{
    // load font
    font = TTF_OpenFont(fontPath, 100);

}
