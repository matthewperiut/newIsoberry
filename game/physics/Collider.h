//
// Created by matthewperiut on 10/22/21.
//

#pragma once

#include <string>
#include "v3.h"

class Collider
{
public:
    // Basic Attributes
    v3 position;
    v3 size;
public:
    // Special functionality
    std::string type = "collider";
    void* ptr[3];
public:
    // Camera
    olc::vf2d* camera = nullptr;
public:
    Collider(v3 position, v3 size);

    // Find Bounds of the Box
    float min(int axis);
    float max(int axis);

    // Useful Functions
    olc::vf2d CornerToScreen(bool mx, bool my, bool mz, bool normalized = false);
    olc::vf2d GetTopLeft();
    olc::vf2d GetBottomRight();
    olc::vf2d Get2DSize();
};