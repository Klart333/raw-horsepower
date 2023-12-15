#pragma once

#include "GameObject.h"
#include "Vector2.h"
#include "Image.h"

struct Cell;

class Pikachu : public GameObject
{
    Cell* CurrentCell;
    Vector2 Heading;
    
public:
    Pikachu(class Transform* InTransform, std::unique_ptr<class Image> InImage);
    void UpdateCurrentCell();
    void UpdateRotation() const;
    void Update(float deltaTime) override;

    void Shoot() const;

    static void CallbackFunction(void* userData)
    {
        static_cast<Pikachu*>(userData)->Shoot();
    }
};
