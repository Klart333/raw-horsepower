#pragma once

class Transform;

class Collider
{
public:
    Transform* TransformRef;

    Collider(Transform*);
};
