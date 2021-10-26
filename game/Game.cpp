//
// Created by matthewperiut on 10/17/21.
//

#define OLC_IMAGE_STB
#define OLC_PGE_APPLICATION

#include "Game.h"
#include "sound/SoundHandler.h"
#include "physics/Collider.h"
#include "draw/Draw.h"
#include "tools/asset/AssetBank.h"
#include "physics/Kinematic.h"
#include "file/ColliderToSprite.h"
#include "file/SaveSprite.h"
#include <iostream>

AssetBank assetBank;

SoundHandler soundHandler;

Kinematic c(v3(0,90,0),v3(5,5,5));
std::vector<Collider*> Colliders;
int assetId;
Sprite* temp = CreateSpriteDebugDraw(c,olc::WHITE);
bool Game::OnUserCreate()
{
    sAppName = "Isoberry";
    soundHandler.LoadSound(GetAssetPath() + "test.wav");

    Colliders.push_back(new Collider(v3(0, 40, 0),v3(10,10,10)));

    std::cout << temp->width << " " << temp->height << std::endl;

    SaveSprite(temp, GetAssetPath() + "output/temp.png");
    //std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    //delete temp;

    assetId = assetBank.LoadPNG(GetAssetPath() + "test/11x25x12TrashBin.png");
    //c.type = "collider_decal";
    //c.ptr[0] = assetBank.GetDecal(assetId);
    c.velocity = v3(0,-20,0);
    c.SetListOfColliders(Colliders);

    SetGameEngine(*this);

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

    Clear(olc::BLACK);
    c.Update(fElapsedTime);
    draw(c);
    draw(*Colliders[0]);
    Draw(pos.toScreen(olc::vf2d(0,0)));

    DrawSprite(vi2d(100,100), temp);
    return 1;
}

bool Game::OnUserDestroy()
{
    assetBank.DeleteImage(assetId);
    return 1;
}
