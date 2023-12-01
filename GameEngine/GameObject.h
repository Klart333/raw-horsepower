#pragma once

class Transform;
class Image;

class GameObject
{
public:
    virtual ~GameObject() = default;
    
    Image* Image;
    Transform* Transform;

    GameObject();

    virtual void Update(const float deltaTime);
    
};

