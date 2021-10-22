//
// Created by matthewperiut on 10/17/21.
//

#include <string>
#include "AssetBank.h"
#include "../../external/olcPixelGameEngine.h"

int AssetBank::LoadPNG(std::string path)
{
    int id = Sprites.size();
    Sprites.push_back(new olc::Sprite(path));
    Decals.push_back(new olc::Decal(reinterpret_cast<olc::Sprite*>(Sprites[id])));
    return id;
}

void AssetBank::DeleteImage(int id)
{
    delete reinterpret_cast<olc::Sprite*>(Sprites[id]);
    delete reinterpret_cast<olc::Decal*>(Decals[id]);
}

void* AssetBank::GetSprite(int id)
{
    return Sprites[id];
}

void* AssetBank::GetDecal(int id)
{
    return Decals[id];
}