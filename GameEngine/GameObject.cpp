#include "GameObject.h"
#include "Transform.h"
#include "Image.h"

GameObject::GameObject(class Transform* InTransform, std::unique_ptr<class Image> InImage):
    Image(std::move(InImage)), Transform(InTransform), Collider(nullptr)
{
}

void GameObject::Update(const float deltaTime)
{
}
