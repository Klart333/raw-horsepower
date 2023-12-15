#pragma once
#include <memory>
// #include "Collider.h"
// #include "Transform.h"


class Collider;
class Transform;
class Image;

class GameObject
{
public:
    virtual ~GameObject() = default;
    
    std::unique_ptr<Image> Image;
    Transform* Transform;
    Collider* Collider;

    GameObject(class Transform* InTransform, std::unique_ptr<class Image> InImage);

    virtual void Update(const float deltaTime);
    
};

