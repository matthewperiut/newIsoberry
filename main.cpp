#include "game/Game.h"

#include "game/tools/settings/Settings.h"
#include "game/tools/asset/AssetPath.h"
Settings settings(GetAssetPath() + "settings.txt");

int main(int argc, char *argv[])
{
    for(int i = 0; i < argc; i++)
    {
        if(std::string(argv[i]) == "-server")
        {

        }
    }

    Game game;
    if(game.Construct(settings.resolution.x,settings.resolution.y,settings.scale,settings.scale,settings.fullscreen,settings.vsync))
        game.Start();
}
