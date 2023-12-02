#include "GameObject.h"
#include "Transform.h"

GameObject::GameObject(): Image(nullptr), Collider(nullptr)
{
    Transform = new class Transform(0, 0, 100, 100);
}

void GameObject::Update(const float deltaTime)
{
    
}


