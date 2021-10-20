//
// Created by matthewperiut on 5/7/21.
//

#include "Native.h"
#include "Settings.h"
#include "Resolution.h"

Settings::Settings(std::string file)
{
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
            mySettingsFile >> resolution.x >> resolution.y;
            resolution = ConvertToHeight(resolution, scale);
        }
        if(output == "vsync")
        {
            mySettingsFile >> vsync;
        }
    }
    if (fullscreen)
    {
        resolution = GetResolution();
    }
    mySettingsFile.close();
}