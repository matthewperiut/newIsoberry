//
// Created by Matthew on 11/12/2021.
//

#include "SettingsInterface.h"
#include "../tools/settings/Settings.h"
#include "../tools/settings/Resolution.h"

extern Settings settings;

SettingsInterface::SettingsInterface() : BaseInterface()
{
    title = "Settings";
    windowSize = {80,50};
    checkbox.emplace_back(settings.fullscreen);
    checkbox.emplace_back(settings.vsync);
    numberbox.emplace_back(settings.resolution.x*settings.scale);
    numberbox.emplace_back(settings.resolution.y*settings.scale);
}

void SettingsInterface::Functionality(PixelGameEngine &g)
{
    g.DrawStringDecal(windowPos + vi2d(6,11), "Fullscreen", olc::BLACK, olc::vf2d(0.75,0.75));
    checkbox[0].position = windowPos + vi2d(68,10);
    checkbox[0].Draw(g);
    g.DrawStringDecal(windowPos + vi2d(6,21), "VSync", olc::BLACK, olc::vf2d(0.75,0.75));
    checkbox[1].position = windowPos + vi2d(38,20);
    checkbox[1].Draw(g);
    g.DrawStringDecal(windowPos + vi2d(6,31), "Resolution", olc::BLACK, olc::vf2d(0.75,0.75));
    numberbox[0].position = windowPos + vi2d(6, 38);
    numberbox[0].Update(g);
    numberbox[1].position = windowPos + vi2d(42, 38);
    numberbox[1].Update(g);
    settings.oldRes = ConvertToHeight(vi2d(numberbox[0].number,numberbox[1].number),settings.scale);
}