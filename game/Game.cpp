//
// Created by matthewperiut on 10/17/21.
//

#define OLC_IMAGE_STB
#define OLC_PGE_APPLICATION

#include "Game.h"
#include "sound/SoundHandler.h"

SoundHandler soundHandler;

bool Game::OnUserCreate() {
    sAppName = "Isoberry";
    soundHandler.LoadSound(GetAssetPath() + "test.wav");
    return 1;
}

bool Game::OnUserUpdate(float fElapsedTime) {
    if (GetKey(olc::ESCAPE).bPressed)
        return 0;
    if (GetKey(olc::A).bPressed)
        soundHandler.Play();
    return 1;
}

bool Game::OnUserDestroy() {
    return 1;
}
