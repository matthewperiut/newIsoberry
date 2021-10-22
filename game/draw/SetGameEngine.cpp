//
// Created by Matthew Periut on 10/22/21.
//

#include "Draw.h"

olc::PixelGameEngine* CurrentEngine;

void SetGameEngine(olc::PixelGameEngine& gameEngine)
{
    CurrentEngine = &gameEngine;
}