//
// Created by matthewperiut on 10/22/21.
//

#pragma once

#include "Collider.h"

class Kinematic : public Collider
{
public:
    // Basic Attributes
    v3 prior; // position
    v3 velocity;
    v3 outPos;
private:
    // Internal Storage
    float elapsedTime;
    std::vector<Collider*>* colliders = nullptr;
public:
    Kinematic(v3 position, v3 size);
    void Update(float fElapsedTime);
    void Move(int axis);

    void SetListOfColliders(std::vector<Collider *> &colliders);

    bool CollidingWithAny(Collider *other);

    Collider *CollidingWithAny();
};
