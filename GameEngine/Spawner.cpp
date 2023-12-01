#include "Spawner.h"

#include "Font.h"
#include "IDisplayWindow.h"
#include "Pikachu.h"
#include "Text.h"
#include "Transform.h"

const char* pikachuImagePath{ "img/pikachu.png" };

Spawner::Spawner()
{
    image_loader = nullptr;
    display_window = nullptr;
}

void Spawner::InitializeGameState(IImageLoader* imageLoader, IDisplayWindow* displayWindow)
{
    image_loader = imageLoader;
    display_window = displayWindow;
    
    // All data related to pikachu
    GameObject* Pickachu = Spawner::Instantiate<Pikachu>();
    Pickachu->Image = get_image(pikachuImagePath, 1);
    Pickachu->Transform = new Transform(0, 0, 200, 200);

    // create text from font
    Text* text = get_text("lazy blah blah", "font/lazy.ttf", 255, 255, 255);

    GameObject* TextObject = Spawner::Instantiate<GameObject>();
    TextObject->Image = text;
    TextObject->Transform = new Transform(200, 400, text->textWidth, text->textHeight);
}

Image* Spawner::get_image(const char* filePath, const int renderOrder) const
{
    return new Image(filePath, image_loader, renderOrder);
}

Text* Spawner::get_text(const char* textString, const char* fontPath, Uint8 r, Uint8 g, Uint8 b) const
{
    Font* font = new Font(fontPath);
    SDL_Color textColor = SDL_Color{ r, g, b, 255 };

    return new Text(display_window->get_Renderer(), font, textColor, textString);
}