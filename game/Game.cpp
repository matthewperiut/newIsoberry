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

Kinematic c(v3(32,90,32),v3(8,8,8));
std::vector<Collider*> Colliders;
int assetId;
Sprite* temp = CreateSpriteDebugDraw(c,olc::WHITE);
bool Game::OnUserCreate()
{
    sAppName = "Isoberry";
    soundHandler.LoadSound(GetAssetPath() + "test.wav");

    bool where[5][5] = {{0,1,1,1,0},
                        {1,1,1,1,0},
                        {1,1,1,1,0},
                        {1,1,1,0,0},
                        {0,0,0,0,0}};

    assetId = assetBank.LoadPNG(GetAssetPath() + "debugtile.png");
    int depth = 5;
    int ct = 5;
    for(int j = 0; j < depth; j++)
    {
        for(int i = 0; i < ct; i++)
        {
            if(where[j][i])
            {
                Colliders.push_back(new Collider(v3(0, 40, 0),v3(16,4,16)));

                Colliders[Colliders.size()-1]->type = "collider_decal";
                Colliders[Colliders.size()-1]->ptr[0] = assetBank.GetDecal(0);
                Colliders[Colliders.size()-1]->position = v3(i*16,40,j*16);
            }
        }
    }


    std::cout << temp->width << " " << temp->height << std::endl;

    SaveSprite(temp, GetAssetPath() + "output/temp.png");
    //std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    //delete temp;

    c.type = "collider_decal";
    assetId = assetBank.LoadPNG(GetAssetPath() + "crate.png");
    c.ptr[0] = assetBank.GetDecal(assetId);;
    c.velocity = v3(0,-20,0);
    c.SetListOfColliders(Colliders);

    SetGameEngine(*this);

    return 1;
}

bool Game::OnUserUpdate(float fElapsedTime)
{
    if (GetKey(olc::ESCAPE).bPressed)
        return 0;
    if (GetKey(olc::F).bPressed)
        soundHandler.Play();

    if (GetKey(olc::A).bHeld)
        c.position.x -= 0.25;
    if (GetKey(olc::D).bHeld)
        c.position.x += 0.25;
    if (GetKey(olc::W).bHeld)
        c.position.z -= 0.25;
    if (GetKey(olc::S).bHeld)
        c.position.z += 0.25;
    if (GetKey(olc::SPACE).bHeld)
        c.position.y += 0.25;

    Clear(olc::Pixel(35,33,61));
    c.Update(fElapsedTime);

    if(c.position.y < 40)
        draw(c);

    for(int i = 0; i < Colliders.size(); i++)
    {
        draw(*Colliders[i]);

        if(GetKey(olc::Key::X).bPressed)
            Colliders[i]->type = "collider";
        if(GetKey(olc::Key::Z).bPressed)
            Colliders[i]->type = "collider_decal";
    }

    if(c.position.y > 40)
        draw(c);



    //DrawDecal(olc::vi2d(0,0),reinterpret_cast<olc::Decal*>(Colliders[0]->ptr[0]));

    //DrawSprite(vi2d(100,100), temp);
    return 1;
}

bool Game::OnUserDestroy()
{
    return 1;
}
