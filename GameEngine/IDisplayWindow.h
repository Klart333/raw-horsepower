#pragma once

class IDisplayWindow
{
public:
    virtual ~IDisplayWindow() = default;

    IDisplayWindow() = default;

    virtual struct SDL_Renderer* get_Renderer() = 0; // Yes I know this makes the interface pointless but to fix it would require so much abstraction
    virtual struct SDL_Window* get_window() = 0;
};
