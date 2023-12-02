#include "CollisionSystem.h"

#include "GameObject.h"
#include "JohnsArray.h"
#include "Transform.h"

void CollisionSystem::Update(const JohnsArray<GameObject>* gameObjects)
{
    for (int i = 0; i < gameObjects->count; i++)
    {
        if (gameObjects->Array[i]->Collider == nullptr)
        {
            continue;
        }

        Transform* bigGuy = gameObjects->Array[i]->Transform;

        for (int g = 0; g < gameObjects->count; g++)
        {
            if (g == i || gameObjects->Array[g]->Collider == nullptr)
            {
                continue;
            }

            const Transform* otherGuy = gameObjects->Array[g]->Transform;

            if (bigGuy->PosX < otherGuy->PosX + otherGuy->Width &&
                bigGuy->PosX + bigGuy->Width > otherGuy->PosX &&
                bigGuy->PosY < otherGuy->PosY + otherGuy->Height &&
                bigGuy->PosY + bigGuy->Height > otherGuy->PosY)
            {
                const Vector2 midPoint = Vector2(bigGuy->PosX + bigGuy->Width / 2.0f, bigGuy->PosY + bigGuy->Height);
                const Vector2 otherMidPoint = Vector2(otherGuy->PosX + otherGuy->Width / 2.0f, otherGuy->PosY + otherGuy->Height);
                Vector2 direction = midPoint - otherMidPoint;
                direction = direction.Normalize();
                direction = direction.Round();
                
                bigGuy->Move(direction);
            }
        }
    }
}
