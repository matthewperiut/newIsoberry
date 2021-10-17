#include "game/Game.h"

#include "game/tools/settings/Settings.h"
#include "game/tools/asset/AssetPath.h"
Settings settings(GetAssetPath() + "settings.txt");

int main()
{
    Game game;
    if(game.Construct(settings.resolution.x,settings.resolution.y,settings.scale,settings.scale,settings.fullscreen,settings.vsync))
        game.Start();
}
