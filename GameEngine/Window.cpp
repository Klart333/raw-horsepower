#include "Window.h"

#include "Cell.h"
#include "GameObject.h"
#include "Grid.h"
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

void Window::render(GameObject* gameObject)
{
    SDL_RenderCopy(window->get_Renderer(), gameObject->Image->getTexture(), nullptr, gameObject->Transform->getRect());
}

void Window::render(Cell* cell)
{
    SDL_RenderCopy(window->get_Renderer(), cell->Image->getTexture(), nullptr, cell->GetRect());
}

void Window::clear() const
{
    SDL_SetRenderDrawColor(window->get_Renderer(), 120, 60, 255, 255);
    SDL_RenderClear(window->get_Renderer());
}

void Window::present()
{
    
}
