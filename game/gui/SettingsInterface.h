//
// Created by Matthew on 11/12/2021.
//

#pragma once
#include "BaseInterface.h"
#include "Checkbox.h"
#include "Numberbox.h"

class SettingsInterface : public BaseInterface
{
public:
    SettingsInterface();
    std::vector<Checkbox> checkbox;
    std::vector<Numberbox> numberbox;

    void Functionality(PixelGameEngine &g) override;
};
