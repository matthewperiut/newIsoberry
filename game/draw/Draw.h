//
// Created by matthewperiut on 10/22/21.
//

#pragma once
#include "../physics/Collider.h"

extern olc::PixelGameEngine* CurrentEngine;

void SetGameEngine(olc::PixelGameEngine& gameEngine);
void draw(Collider& collider);