//
// Created by matthewperiut on 10/17/21.
//

#include <string>
#include "AssetBank.h"
#include "../../external/olcPixelGameEngine.h"

int AssetBank::LoadPNG(std::string path)
{
    int id = Sprites.size();

    for(int i = 0; i < filepath.size(); i++)
    {
        if(filepath[i] == path)
            return i;
    }

    filepath.push_back(path);
    Sprites.push_back(new olc::Sprite(path));
    Decals.push_back(new olc::Decal(reinterpret_cast<olc::Sprite*>(Sprites[id])));
    return id;
}

void AssetBank::DeleteImage(int id)
{
    filepath.erase(filepath.begin()+id);
    delete reinterpret_cast<olc::Sprite*>(Sprites[id]);
    Sprites.erase(Sprites.begin()+id);
    delete reinterpret_cast<olc::Decal*>(Decals[id]);
    Decals.erase(Decals.begin()+id);
}

void* AssetBank::GetSprite(int id)
{
    return Sprites[id];
}

void* AssetBank::GetDecal(int id)
{
    return Decals[id];
}

AssetBank::~AssetBank()
{
    for(int i = 0; i < Sprites.size(); i++)
    {
        DeleteImage(i);
    }
}
