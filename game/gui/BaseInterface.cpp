//
// Created by matthewperiut on 11/1/2021.
//

#include "BaseInterface.h"
#include "../tools/asset/AssetPath.h"

std::vector<void*> interfaces;
vi2d mousePos;

bool initialized;
olc::Pixel color{255,255,255,128};
olc::Pixel textColor{0,0,0,255};
Sprite* buttonSpr;
Sprite* cornerSpr;
Sprite* singleSpr;
Decal* button;
Decal* corner;
Decal* single;

BaseInterface::BaseInterface()
{
    interfaces.push_back(this);
}

void BaseInterface::Initialize()
{
    if(initialized)
        return;
    initialized = true;
    buttonSpr = new Sprite(GetAssetPath() + "gui/button.png");
    cornerSpr = new Sprite(GetAssetPath() + "gui/corner.png");
    singleSpr = new Sprite(1,1);
    singleSpr->SetPixel(0,0,olc::WHITE);
    button = new Decal(buttonSpr);
    corner = new Decal(cornerSpr);
    single = new Decal(singleSpr);
}

void BaseInterface::UpdateMousePos(vi2d pos)
{
    mousePos = pos;
}

void BaseInterface::DrawBox(PixelGameEngine &g)
{
    vi2d& pos = windowPos;
    vi2d& size = windowSize;

    // Corner Size
    cs = {cornerSpr->width, cornerSpr->height};

    // Top Left, Top Right Corners
    g.DrawDecal(pos, corner, vf2d(1, 1), color);
    g.DrawDecal(pos + vf2d(size.x, 0), corner, vf2d(-1, 1), color);

    // Top Bridge
    g.DrawDecal(pos + vf2d(cs.x, 0), single, vf2d(size.x-(cs.x*2),cs.y), color);

    // Top Line
    g.DrawDecal(pos + vf2d(cs.x/2, cs.y), single, vf2d(size.x - (cs.x), 0.5), textColor);

    // Middle
    g.DrawDecal(pos + vf2d(0, cs.y), single, vf2d(size.x, size.y - cs.y*2), color);

    // Bottom Left, Bottom Right Corners
    g.DrawDecal(pos + vf2d(0, size.y), corner, vf2d(1, -1), color);
    g.DrawDecal(pos + vf2d(size.x, size.y), corner, vf2d(-1, -1), color);

    // Bottom Bridge
    g.DrawDecal(pos + vf2d(cs.x, size.y-cs.y), single, vf2d(size.x - cs.x * 2, cs.y), color);

    //Top Line
    g.DrawDecal(pos + vf2d(cs.x/2, cs.y), single, vf2d(size.x - (cs.x), 0.5), textColor);
    // Title
    g.DrawStringDecal(pos + vf2d(cs.x / 1.5, cs.y/4), title, textColor, vf2d(0.75,0.75));
    // Close Button
    closeButtonLocation = pos + vf2d(size.x - cs.x * 1.5, 0);
    g.DrawDecal(closeButtonLocation, button, vf2d(1, 1), Pixel(217, 87, 99));
}

void BaseInterface::DrawAll(PixelGameEngine &g)
{
    BaseInterface::UpdateMousePos(g.GetMousePos());
    for(int i = 0; i < interfaces.size(); i++)
    {
        BaseInterface& base = *reinterpret_cast<BaseInterface*>(interfaces[i]);
        if(base.Closing(g))
        {
            // This trick is to ensure the latest opened window is put on top
            interfaces.erase(interfaces.begin()+i);
            interfaces.push_back(reinterpret_cast<void*>(&base));
            break;
        }
        if(base.hidden)
            continue;
        base.Dragging(g);
        base.DrawBox(g);
        base.Resizing(g);
        base.Functionality(g);
        if(base.startedHolding)
        {
            base.startedHolding = false;
            interfaces.erase(interfaces.begin()+i);
            interfaces.push_back(reinterpret_cast<void*>(&base));
            break;
        }
    }
}

void BaseInterface::Functionality(PixelGameEngine &g)
{

}

void BaseInterface::Resizing(PixelGameEngine &g)
{
    // No need for this atm.
}

bool BaseInterface::Closing(PixelGameEngine &g)
{
    if(g.GetKey(opening).bPressed)
    {
        hidden = !hidden;
        if(!hidden)
            return true;
    }

    if(hidden)
        return false;
    if (g.GetMouse(0).bPressed)
    {
        if (mousePos.x > closeButtonLocation.x && mousePos.y > closeButtonLocation.y)
        {
            if (mousePos.x < closeButtonLocation.x + 8 && mousePos.y < closeButtonLocation.y + 8)
            {
                hidden = true;
                holding = false;
            }
        }
    }
    return false;
}

void BaseInterface::Dragging(PixelGameEngine &g)
{
    if (g.GetMouse(0).bPressed)
    {
        if (mousePos.x > windowPos.x && mousePos.y > windowPos.y)
        {
            if (mousePos.x < windowPos.x + windowSize.x && mousePos.y < windowPos.y + cs.y)
            {
                startedHolding = true;
                holding = true;
                displacement = windowPos - mousePos;
            }
        }
    }
    if (holding)
    {
        windowPos = displacement + mousePos;
    }
    if (g.GetMouse(0).bReleased)
    {
        holding = false;
    }
}

void BaseInterface::Deinitialize()
{
    if(!initialized)
        return;
    initialized = false;
    delete buttonSpr;
    delete cornerSpr;
    delete singleSpr;
    delete button;
    delete corner;
    delete single;
}


BaseInterface::~BaseInterface()
{
    for(int i = 0; i < interfaces.size(); i++)
    {
        if(interfaces[i] == this)
            interfaces.erase(interfaces.begin() + i);
    }
}

