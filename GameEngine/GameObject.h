#pragma once
// #include "Collider.h"
// #include "Transform.h"


class Collider;
class Transform;
class Image;

class GameObject
{
public:
    virtual ~GameObject() = default;
    
    Image* Image;
    Transform* Transform;
    Collider* Collider;

    GameObject(class Transform* InTransform, class Image* InImage);

    virtual void Update(const float deltaTime);
    
};

