//
// Created by matthewperiut on 11/12/21.
//

#pragma once
#include "BaseInterface.h"
#include "Checkbox.h"

void GUIInit()
{
    BaseInterface::Initialize();
    Checkbox::Initialize();
}

void GUIExit()
{
    BaseInterface::Deinitialize();
    Checkbox::Deinitialize();
}