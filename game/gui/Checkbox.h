//
// Created by Matthew on 11/12/2021.
//

#pragma once

#include "../external/olcPixelGameEngine.h"

class Checkbox
{
public:
    olc::vi2d position;
    bool state = false;

    void Draw(olc::PixelGameEngine &g);
};