#include "GameObject.h"
#include "Transform.h"
#include "Image.h"

GameObject::GameObject(class Transform* InTransform, class Image* InImage):
    Image(InImage), Transform(InTransform), Collider(nullptr)
{
}

void GameObject::Update(const float deltaTime)
{
}
