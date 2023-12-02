#include "Pikachu.h"

#include <cmath>

#include "Cell.h"
#include "Collider.h"
#include "Dependencies.h"
#include "Grid.h"
#include "InputManager.h"
#include "Spawner.h"
#include "Text.h"
#include "Transform.h"

const char* charmanderImagePath{"img/charmander.png"};

Pikachu::Pikachu(class Transform* InTransform, class Image* InImage)
    : GameObject(InTransform, InImage)
{
    CurrentCell = nullptr;
    velocity = Vector2(0, 0);
    Dependencies::instance()->InputManager->AddFunctionPointerToMouseButtonClicked(&Pikachu::CallbackFunction, this);

    this->Collider = new class Collider(this->Transform);
}

void Pikachu::UpdateCurrentCell()
{
    int x = round(Transform->PosX / CellSize);
    int y = round(Transform->PosY / CellSize);
    CurrentCell = Dependencies::instance()->Grid->TheGrid[x][y];
}

void Pikachu::Update(const float deltaTime)
{
    GameObject::Update(deltaTime);

    UpdateCurrentCell();

    velocity = velocity * std::pow(0.01f, deltaTime);

    int x = Dependencies::instance()->InputManager->Horizontal;
    int y = Dependencies::instance()->InputManager->Vertical;

    const int gridIndexX = CurrentCell->X + x;
    const int gridIndexY = CurrentCell->Y + y;
    if (!Dependencies::instance()->Grid->TheGrid[gridIndexX][gridIndexY]->Walkable)
    {
        x = 0;
        y = 0;
        velocity = velocity * 0;
    }

    velocity = velocity + Vector2(static_cast<float>(x), static_cast<float>(y));

    Transform->Move(velocity * deltaTime * 1);
}

void Pikachu::Shoot() const
{
    //velocity = velocity * 2;

    GameObject* gm = Spawner::Instantiate<GameObject>(
        new class Transform(Transform->PosX, Transform->PosY, 100, 100),
        Dependencies::instance()->Spawner->get_image(charmanderImagePath, 0));
}
