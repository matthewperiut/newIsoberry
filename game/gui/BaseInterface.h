//
// Created by matthewperiut on 11/1/2021.
//

#pragma once

#include "../external/olcPixelGameEngine.h"

using namespace olc;

class BaseInterface
{
private:
    bool startedHolding = false;
    bool holding = false;
    bool hidden = true;

    vi2d cs;
    vi2d displacement{0,0};
    vi2d closeButtonLocation{-8,-8};
public:
    olc::Key opening = olc::Key::P;
    std::string title = "none";

    bool resize = false;
    vi2d windowPos{20,20};
    vi2d windowSize{100,100};

    BaseInterface();
    ~BaseInterface();

public:
    static void Initialize();
    static void DrawAll(PixelGameEngine& g);
    static void Deinitialize();

    static void UpdateMousePos(vi2d pos);

public:
    void Resizing(PixelGameEngine& g);
    bool Closing(PixelGameEngine& g);
    void Dragging(PixelGameEngine& g);

    void DrawBox(PixelGameEngine &g);

    virtual void Functionality(PixelGameEngine &g);
};
