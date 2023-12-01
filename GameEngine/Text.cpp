#include "Text.h"

#include <SDL_surface.h>
#include <SDL_ttf.h>

#include "Font.h"


Text::Text(SDL_Renderer* renderer, const Font* font, SDL_Color& textColor, const char* text)
{
    this->textColor = &textColor;
    // render the text into an unoptimized CPU surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font->getFont(), text, textColor);
    if (textSurface == nullptr)
    {
        //printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }
    else
    {
        // Create texture GPU-stored texture from surface pixels
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);

        if (texture == nullptr)
        {
            //printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
            return;
        }
        
        // Get image dimensions
        int width = textSurface->w;
        int height = textSurface->h;
        this->textWidth = textSurface->w;
        this->textHeight = textSurface->h;
        //Get rid of old loaded surface
        SDL_FreeSurface(textSurface);
    }
}