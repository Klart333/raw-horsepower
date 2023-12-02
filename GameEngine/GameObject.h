#pragma once

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

    GameObject();

    virtual void Update(const float deltaTime);
    
};

