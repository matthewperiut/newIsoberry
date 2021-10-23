//
// Created by Matthew Periut on 10/22/21.
//

#include "Kinematic.h"

Kinematic::Kinematic(v3 position, v3 size) : Collider(position, size)
{

}

void Kinematic::SetListOfColliders(std::vector<Collider*> &colliders)
{
    this->colliders = &colliders;
}

void Kinematic::Update(float fElapsedTime)
{
    if(fElapsedTime > 1)
        return;

    prior = position;
    elapsedTime = fElapsedTime;

    for(int i = 0; i < 3; i++)
    {
        Move(i);
    }
    position = outPos;
}

Collider* Kinematic::CollidingWithAny()
{
    if(this->colliders == nullptr)
        return nullptr;

    for(auto & collider : *colliders)
    {
        if(collider->isColliding(*this))
        {
            return collider;
        }
    }
    return nullptr;
}

void Kinematic::Move(int axis)
{
    position = prior;
    position += velocity * v3(axis == 0, axis % 2, int(axis/2)) * elapsedTime;
    bool positive = velocity.get(axis) > 0;

    Collider *collidingWith = CollidingWithAny();
    if(collidingWith != nullptr)
    {
        outPos.get(axis) = prior.get(axis);

        if(positive)
        {
            outPos.get(axis) = collidingWith->min(axis) - size.get(axis);
        }
        else
        {
            outPos.get(axis) = collidingWith->max(axis);
        }
    }
    else
    {
        outPos.get(axis) = position.get(axis);
    }
}
