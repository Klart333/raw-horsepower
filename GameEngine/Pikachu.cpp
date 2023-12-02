#include "Pikachu.h"

#include <cmath>

#include "Dependencies.h"
#include "InputManager.h"
#include "Transform.h"

Pikachu::Pikachu()
{
    velocity = Vector2(0, 0);
    Dependencies::instance()->InputManager->AddFunctionPointerToMouseButtonClicked(&Pikachu::CallbackFunction, this);
}

void Pikachu::Update(const float deltaTime)
{
    GameObject::Update(deltaTime);

    velocity = velocity * std::pow(0.01f, deltaTime);

    const int x = Dependencies::instance()->InputManager->Horizontal;
    const int y = Dependencies::instance()->InputManager->Vertical;
    velocity = velocity + Vector2(static_cast<float>(x), static_cast<float>(y)); 
    
    Transform->Move(velocity * deltaTime * 1);
}

void Pikachu::Shoot()
{
    velocity = velocity * 2;
}

