#pragma once
#include <SDL_stdinc.h>
#include "Dependencies.h"
#include "GameManager.h"

class Text;
class Image;
class Transform;
class IDisplayWindow;
class IImageLoader;
class GameObject;

class Spawner
{
    IImageLoader* image_loader; 
    IDisplayWindow* display_window;
    
public:
    Spawner();

    void InitializeGameState(IImageLoader*, IDisplayWindow*);

    Image* get_image(const char* filePath, int renderOrder = 0) const;
    Text* get_text(const char* textString, const char* fontPath, Uint8 r = 255, Uint8 g = 255, Uint8 b = 255) const;

    template<typename T>
    static T* Instantiate(); 
};

template<typename T>
T* Spawner::Instantiate()
{
    T* object = new T();
    
    Dependencies::instance()->GameManager->AddGameObject(object);
    
    return object;
}
