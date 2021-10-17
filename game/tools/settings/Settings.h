//
// Created by matthewperiut on 5/7/21.
//

#pragma once

#include "Resolution.h"
#include <iostream>
#include <fstream>
#include <string>

class Settings
{
public:
    Settings(std::string file);
    bool vsync{ true };
    bool fullscreen{ false };

    int scale{ 4 };
    olc::vi2d resolution{0,0};
};