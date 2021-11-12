//
// Created by matthewperiut on 5/7/21.
//

#include "Native.h"
#include "Settings.h"
#include "Resolution.h"

Settings::Settings(std::string file)
{
    filename = file;
    vi2d screenSize = GetResolution();
    resolution = vi2d(NATIVESCREENWIDTH, NATIVESCREENHEIGHT);

    if(!std::filesystem::exists(file))
    {
        std::ofstream createFile(file);
        createFile.close();
    }

    std::ifstream mySettingsFile(file);
    std::string output;
    while(mySettingsFile >> output)
    {
        if(output == "fullscreen")
        {
            mySettingsFile >> fullscreen;
        }
        if(output == "resolution")
        {
            mySettingsFile >> oldRes.x >> oldRes.y;
            if(!oldRes.x < NATIVESCREENWIDTH && !oldRes.y < NATIVESCREENHEIGHT)
            {
                if(!oldRes.x > screenSize.x && !oldRes.x > screenSize.y)
                {
                    resolution = ConvertToHeight(oldRes, scale);
                }
            }
            oldRes = {0,0};
        }
        if(output == "vsync")
        {
            mySettingsFile >> vsync;
        }
    }
    if (fullscreen)
    {
        oldRes = resolution;
        resolution = screenSize;
    }
    mySettingsFile.close();
}

Settings::~Settings()
{
    std::filesystem::remove(filename);
    std::ofstream mySettingsFile(filename);
    mySettingsFile << "fullscreen " << fullscreen << '\n';
    vi2d& res = oldRes.x != 0 ? oldRes : resolution;
    mySettingsFile << "resolution " << res.x*scale << " " << res.y*scale << '\n';
    mySettingsFile << "vsync " << vsync << '\n';
}
