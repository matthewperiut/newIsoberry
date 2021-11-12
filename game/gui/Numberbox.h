//
// Created by matthewperiut on 11/12/21.
//

#pragma once

#include "../external/olcPixelGameEngine.h"

class Numberbox
{
public:
    std::string text;
    int number;
    bool focused;
    int limit = 4;
    olc::vi2d position;
    olc::vi2d size{30,8};
    Numberbox(int number);
    void Update(olc::PixelGameEngine &g);
};