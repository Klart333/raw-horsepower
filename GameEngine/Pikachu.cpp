
#include "Pikachu.h"
#include <cmath>

#include "Cell.h"
#include "Collider.h"
#include "Dependencies.h"
#include "Grid.h"
#include "InputManager.h"
#include "Text.h"
#include "Transform.h"

const char* charmanderImagePath{"img/charmander.png"};

Pikachu::Pikachu(class Transform* InTransform, std::unique_ptr<class Image> InImage)
    : GameObject(InTransform, std::move(InImage))
{
    CurrentCell = nullptr;
    Dependencies::instance()->InputManager->AddFunctionPointerToMouseButtonClicked(&Pikachu::CallbackFunction, this);

    this->Collider = new class Collider(this->Transform);
}

void Pikachu::UpdateCurrentCell()
{
    const int x = round(Transform->PosX / CellSize);
    const int y = round(Transform->PosY / CellSize);

    CurrentCell = Dependencies::instance()->Grid->TheGrid[x][y];
    if (CurrentCell->CointainsCoin)
    {
        CurrentCell->CointainsCoin = false;
    }
}

void Pikachu::UpdateRotation() const
{
    if (Heading.x < 0) // was in order before
    {
        Transform->Rotation = 2;
    }
    else if (Heading.y > 0)
    {
        Transform->Rotation = 1;
    }
    else if (Heading.x > 0)
    {
        Transform->Rotation = 0;
    }
    else if (Heading.y < 0)
    {
        Transform->Rotation = 3;
    }
}

void Pikachu::Update(const float deltaTime)
{
    GameObject::Update(deltaTime);

    const int x = Dependencies::instance()->InputManager->Horizontal;
    const int y = Dependencies::instance()->InputManager->Vertical;

    if (x == 0 && y == 0)
    {
        return;
    }

    UpdateCurrentCell();
    UpdateRotation();

    Heading = Vector2(x, y);
    
    const int gridIndexX = CurrentCell->X + x;
    const int gridIndexY = CurrentCell->Y + y;
    if (!Dependencies::instance()->Grid->TheGrid[gridIndexX][gridIndexY]->Walkable)
    {
        return;
    }

    const Vector2 movement = Vector2(x, y);
    Transform->Move(movement * deltaTime * 40);
}

void Pikachu::Shoot() const
{
    if (Heading.x == 0 && Heading.y == 0)
    {
        return;
    }
    
    int x = Heading.x;
    int y = Heading.y;
    while (!Dependencies::instance()->Grid->TheGrid[CurrentCell->X + x][CurrentCell->Y + y]->Walkable)
    {
        x += Heading.x;
        y += Heading.y;

        if (!(CurrentCell->X + x < GridX && CurrentCell->X + x >= 0 && CurrentCell->Y + y < GridY && CurrentCell->Y + y >= 0))
        {
            return;
        }
    }
    
    Transform->Move(x * CellSize, y * CellSize);
}
