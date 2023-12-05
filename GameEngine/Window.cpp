#include "Window.h"

#include "Cell.h"
#include "GameObject.h"
#include "IDisplayWindow.h"
#include "IImageLoader.h"
#include "Transform.h"

Window::Window(IDisplayWindow* displayWindow, IImageLoader* imageLoader)
{
    this->window = displayWindow;

    this->imageLoader = imageLoader;
    this->success = true;
}

Window::~Window()
{
    
}

void Window::render(GameObject* gameObject) const
{
    SDL_RenderCopy(window->get_Renderer(), gameObject->Image->getTexture(), nullptr, gameObject->Transform->getRect());
}

void Window::render(Cell* cell) const
{
    SDL_RenderCopyEx(window->get_Renderer(), cell->Image->getTexture(), nullptr, cell->GetRect(), cell->Image->AngleDeg, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
}

void Window::render(SDL_Texture* img, const SDL_Rect* rect, int angle) const
{
    SDL_RenderCopyEx(window->get_Renderer(), img, nullptr, rect, angle, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
}

void Window::clear() const
{
    SDL_SetRenderDrawColor(window->get_Renderer(), 120, 60, 255, 255);
    SDL_RenderClear(window->get_Renderer());
}

void Window::present()
{
    
}
