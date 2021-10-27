#include "game/Game.h"

#include "game/tools/settings/Settings.h"
#include "game/tools/asset/AssetPath.h"
#include "game/network/server/IsoServer.h"

Settings settings(GetAssetPath() + "settings.txt");

#include <yojimbo.h>
#include <mbedtls/version.h>

#ifdef WIN32
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

void TemporaryCMD(bool& running)
{
    while(running)
    {
        std::string input;
        std::cin >> input;
        if(input == "exit")
            break;
    }
    running = false;
}

int main(int argc, char *argv[])
{
    std::cout << MBEDTLS_VERSION_MAJOR << std::endl;

    for(int i = 0; i < argc; i++)
    {
        if(std::string(argv[i]) == "-server")
        {
            IsoServer isoServer(yojimbo::Address("10.0.0.11"));
            std::thread thread(TemporaryCMD, std::ref(isoServer.m_running));
            isoServer.Run();
        }
    }

    Game game;
    if(game.Construct(settings.resolution.x,settings.resolution.y,settings.scale,settings.scale,settings.fullscreen,settings.vsync))
        game.Start();
}
