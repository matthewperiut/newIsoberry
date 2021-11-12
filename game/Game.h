//
// Created by matthewperiut on 10/17/21.
//

#pragma once

#include "external/olcPixelGameEngine.h"
#include "gui/SettingsInterface.h"

using namespace olc;

class Game : public PixelGameEngine
{
    SettingsInterface inter;
    BaseInterface basisInter;

    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
    bool OnUserDestroy() override;
};