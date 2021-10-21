//
// Created by matthewperiut on 10/17/21.
//

#define OLC_IMAGE_STB
#define OLC_PGE_APPLICATION

#include "Game.h"

#define OLC_PGEX_SOUND
#include "external/olcPGEX_Sound.h"

#include <list>

int snd;

bool Game::OnUserCreate() {
    sAppName = "Isoberry";

    olc::SOUND::InitialiseAudio();
    snd = olc::SOUND::LoadAudioSample(GetAssetPath() + "test.wav");
    return 1;
}

bool Game::OnUserUpdate(float fElapsedTime) {
    if (GetKey(olc::ESCAPE).bPressed)
        return 0;
    if (GetKey(olc::A).bPressed)
        olc::SOUND::PlaySample(snd);
    return 1;
}

bool Game::OnUserDestroy() {
    return 1;
}
