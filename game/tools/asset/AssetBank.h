//
// Created by matthewperiut on 10/17/21.
//

#pragma once

#include <vector>


class AssetBank
{
public:
    std::vector<std::string> filepath;
    std::vector<void*> Sprites;
    std::vector<void*> Decals;

public:
    int LoadPNG(std::string path);
    void DeleteImage(int id);

    void *GetSprite(int id);
    void *GetDecal(int id);
};
