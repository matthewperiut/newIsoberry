//
// Created by Matthew on 11/12/2021.
//

#pragma once

#include "../external/olcPixelGameEngine.h"

class Checkbox
{
public:
    Checkbox(bool& boolean);

    olc::vi2d position;
    bool* state;

    void Draw(olc::PixelGameEngine &g);

    static void Initialize();
    static void Deinitialize();
};