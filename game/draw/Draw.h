//
// Created by matthewperiut on 10/22/21.
//

#pragma once
#import "../physics/Collider.h"

extern olc::PixelGameEngine* CurrentEngine;

void SetGameEngine(olc::PixelGameEngine& gameEngine);
void draw(Collider& collider);