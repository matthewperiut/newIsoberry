//
// Created by Matthew on 11/12/2021.
//

#include "Checkbox.h"
#include "../tools/asset/AssetPath.h"

using namespace olc;
static Sprite* checkSpr;
static Decal* check;
static Sprite* crossSpr;
static Decal* cross;

Checkbox::Checkbox(bool &boolean)
{
    state = &boolean;
}

void Checkbox::Draw(olc::PixelGameEngine &g)
{
    g.DrawDecal(position, *state ? check : cross, vf2d(0.5,0.5));

    vi2d mousePos = g.GetMousePos();
    if (g.GetMouse(0).bPressed)
        if (mousePos.x > position.x && mousePos.y > position.y)
            if (mousePos.x < position.x + 8 && mousePos.y < position.y + 8)
                *state = !*state;
}

void Checkbox::Initialize()
{
    checkSpr = new Sprite(GetAssetPath() + "gui/checkmark.png");
    crossSpr = new Sprite(GetAssetPath() + "gui/crossout.png");
    check = new Decal(checkSpr);
    cross = new Decal(crossSpr);
}

void Checkbox::Deinitialize()
{
    delete checkSpr;
    delete crossSpr;
    delete check;
    delete cross;
}