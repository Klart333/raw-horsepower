#include "Pikachu.h"

#include <cmath>

#include "Collider.h"
#include "Dependencies.h"
#include "InputManager.h"
#include "Spawner.h"
#include "Transform.h"

const char* charmanderImagePath{ "img/charmander.png" };

Pikachu::Pikachu()
{
    velocity = Vector2(0, 0);
    Dependencies::instance()->InputManager->AddFunctionPointerToMouseButtonClicked(&Pikachu::CallbackFunction, this);

    this->Collider = new class Collider(this->Transform);
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
    //velocity = velocity * 2;

    GameObject* gm = Spawner::Instantiate<GameObject>();
    gm->Image = Dependencies::instance()->Spawner->get_image(charmanderImagePath, 0);
    gm->Transform->SetPosition(this->Transform->PosX, this->Transform->PosY);
    gm->Collider = new class Collider(gm->Transform);
}

