//
// Created by Matthew on 11/12/2021.
//

#pragma once
#include "BaseInterface.h"

class SettingsInterface : public BaseInterface
{
public:
    SettingsInterface();

    void Functionality(PixelGameEngine &g) override;
};
