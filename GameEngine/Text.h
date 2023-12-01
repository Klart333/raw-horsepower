#pragma once
#include <SDL_render.h>
#include "Image.h"

class Font;

class Text : public Image
{
    // create text from font
    SDL_Color* textColor;
    
    public:
    //Render text surface
    int textWidth; 
    int textHeight;
    
    Text(SDL_Renderer* renderer, const Font* font, SDL_Color& textColor, const char* text);
};
