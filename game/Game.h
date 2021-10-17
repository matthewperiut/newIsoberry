//
// Created by matthewperiut on 10/17/21.
//

#pragma once

#include "external/olcPixelGameEngine.h"

using namespace olc;

class Game : public PixelGameEngine
{
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
    bool OnUserDestroy() override;
};