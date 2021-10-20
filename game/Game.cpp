//
// Created by matthewperiut on 10/17/21.
//

#define OLC_IMAGE_STB
#define OLC_PGE_APPLICATION

#include "Game.h"

bool Game::OnUserCreate() {
    sAppName = "Isoberry";
    return 1;
}

bool Game::OnUserUpdate(float fElapsedTime) {
    if (GetKey(olc::ESCAPE).bPressed)
        return 0;
    return 1;
}

bool Game::OnUserDestroy() {
    return 1;
}
