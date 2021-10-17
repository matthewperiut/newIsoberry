//
// Created by matthewperiut on 5/11/21.
//

#include "AssetPath.h"

#ifdef __APPLE__
    #include <mach-o/dyld.h>

    std::string GetAssetPath()
    {
        static std::string pathStr;

        if (pathStr.empty())
        {
            char path[1024];
            uint32_t size = sizeof(path);
            if (_NSGetExecutablePath(path, &size) == 0)
                pathStr = path;
            else
                printf("buffer too small; need size %u\n", size);

            pathStr.erase(pathStr.begin()+pathStr.find("MacOS/Isoberry"), pathStr.end());
            pathStr += "assets/";
        }

        return pathStr;
    }
#endif
#if defined(_WIN32) || defined(__linux__)
    std::string GetAssetPath()
    {
        return "./assets/";
    }
#endif
