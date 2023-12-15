#pragma once
#include <memory>
#include <SDL_stdinc.h>
#include "Dependencies.h"
#include "GameManager.h"
#include "Image.h"

class Text;
//class Image;
class Transform;
class IDisplayWindow;
class IImageLoader;
class GameObject;

class Spawner
{
    IDisplayWindow* display_window;
    
public:
    Spawner();
    void InitializeInterfaces(IImageLoader* imageLoader, IDisplayWindow* displayWindow);

    IImageLoader* image_loader; 
    
    void InitializeGameState() const;

    std::unique_ptr<Image> get_image(const char* filePath, int renderOrder = 0, int angle = 0) const;
    Text* get_text(const char* textString, const char* fontPath, Uint8 r = 255, Uint8 g = 255, Uint8 b = 255) const;

    template<typename T>
    static T* Instantiate(Transform* InTransform, std::unique_ptr<Image> InImage); 
};

template<typename T>
T* Spawner::Instantiate(Transform* InTransform, std::unique_ptr<Image> InImage)
{
    T* object = new T(InTransform, std::move(InImage));
    
    Dependencies::instance()->GameManager->AddGameObject(object);
    
    return object;
}
