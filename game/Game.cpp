//
// Created by matthewperiut on 10/17/21.
//

#define OLC_IMAGE_STB
#define OLC_PGE_APPLICATION

#include "Game.h"
#include "sound/SoundHandler.h"
#include "physics/Collider.h"
#include "draw/Draw.h"

SoundHandler soundHandler;


bool Game::OnUserCreate()
{
    sAppName = "Isoberry";
    soundHandler.LoadSound(GetAssetPath() + "test.wav");

    Collider c(v3(1,1,1),v3(20,20,10));
    SetGameEngine(*this);
    draw(c);

    return 1;
}

bool Game::OnUserUpdate(float fElapsedTime)
{
    static v3 pos;

    if (GetKey(olc::ESCAPE).bPressed)
        return 0;
    if (GetKey(olc::F).bPressed)
        soundHandler.Play();

    if (GetKey(olc::A).bHeld)
        pos.x -= 0.25;
    if (GetKey(olc::D).bHeld)
        pos.x += 0.25;
    if (GetKey(olc::W).bHeld)
        pos.z -= 0.25;
    if (GetKey(olc::S).bHeld)
        pos.z += 0.25;
    if (GetKey(olc::SPACE).bHeld)
        pos.y += 0.25;

    Draw(pos.toScreen(olc::vf2d(0,0)));
    return 1;
}

bool Game::OnUserDestroy()
{
    return 1;
}
