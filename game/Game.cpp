//
// Created by matthewperiut on 10/17/21.
//

#define OLC_IMAGE_STB
#define OLC_PGE_APPLICATION

#include "Game.h"
#include "sound/SoundHandler.h"
#include "physics/v3.h"
#include "physics/Collider.h"
#include "physics/Box.h"

SoundHandler soundHandler;

Collider c(v3(1,1,1),v3(20,20,10));
bool Game::OnUserCreate() {
    sAppName = "Isoberry";
    soundHandler.LoadSound(GetAssetPath() + "test.wav");

    for(int i = 0; i < 12; i++)
    {
        DrawLine(c.CornerToScreen(box[i][0][0],box[i][0][1],box[i][0][2]),
                 c.CornerToScreen(box[i][1][0],box[i][1][1],box[i][1][2]));
    }

    std::cout << c.Get2DSize() << std::endl;
    Draw(c.CornerToScreen(0,1,0),olc::RED);

    return 1;
}

v3 pos;
bool Game::OnUserUpdate(float fElapsedTime) {
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

bool Game::OnUserDestroy() {
    return 1;
}
