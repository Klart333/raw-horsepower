#include "Spawner.h"

#include <memory>

#include "Font.h"
#include "IDisplayWindow.h"
#include "Pikachu.h"
#include "Text.h"
#include "Transform.h"

const char* pikachuImagePath{"img/pikachu.png"};

Spawner::Spawner()
{
    image_loader = nullptr;
    display_window = nullptr;
}

void Spawner::InitializeInterfaces(IImageLoader* imageLoader, IDisplayWindow* displayWindow)
{
    image_loader = imageLoader;
    display_window = displayWindow;
}

void Spawner::InitializeGameState() const
{
    // All data related to pikachu
    GameObject* Pickachu = Spawner::Instantiate<Pikachu>(
        new Transform(1920 / 2, 1080 / 2, 20, 20),
        get_image(pikachuImagePath, 1));

    // create text from font
    //Text* text = get_text("lazy blah blah", "font/lazy.ttf", 255, 255, 255);

    //GameObject* TextObject = Spawner::Instantiate<GameObject>(
    //    new Transform(200, 400, text->textWidth, text->textHeight),
    //    text);
}

std::unique_ptr<Image> Spawner::get_image(const char* filePath, const int renderOrder, const int angle) const
{
    return std::make_unique<Image>(filePath, renderOrder, angle);
}

Text* Spawner::get_text(const char* textString, const char* fontPath, Uint8 r, Uint8 g, Uint8 b) const
{
    Font* font = new Font(fontPath);
    SDL_Color textColor = SDL_Color{r, g, b, 255};

    return new Text(display_window->get_Renderer(), font, textColor, textString);
}
