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
    IDisplayWindow* display_window;
    
public:
    Spawner();

    IImageLoader* image_loader; 
    
    void InitializeGameState(IImageLoader*, IDisplayWindow*);

    Image* get_image(const char* filePath, int renderOrder = 0, int angle = 0) const;
    Text* get_text(const char* textString, const char* fontPath, Uint8 r = 255, Uint8 g = 255, Uint8 b = 255) const;

    template<typename T>
    static T* Instantiate(Transform* InTransform, Image* InImage); 
};

template<typename T>
T* Spawner::Instantiate(Transform* InTransform, Image* InImage)
{
    T* object = new T(InTransform, InImage);
    
    Dependencies::instance()->GameManager->AddGameObject(object);
    
    return object;
}
