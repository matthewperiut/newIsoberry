//
// Created by matthewperiut on 11/12/21.
//

#include "Numberbox.h"


using namespace olc;
extern Decal* single;

Numberbox::Numberbox(int number)
{
    this->number = number;
    text = std::to_string(number);
}

void Numberbox::Update(olc::PixelGameEngine &g)
{
    g.DrawDecal(position+size,single,vf2d(1,1));
    g.DrawDecal(position,single,vf2d(size.x+1,1));
    g.DrawDecal(position,single,vf2d(1,size.y+1));
    g.DrawDecal(position+size,single,vf2d(-size.x,1));
    g.DrawDecal(position+size,single,vf2d(1,-size.y));
    g.DrawStringDecal(position + vi2d(2,2),text,olc::BLACK,vf2d(0.75,0.75));

    vi2d mousePos = g.GetMousePos();

    if(g.GetMouse(0).bPressed)
    {
        if(mousePos.x > position.x && mousePos.y > position.y)
        {
            if(mousePos.x < position.x + size.x && mousePos.y < position.y + size.y)
            {
                focused = true;
            }
            else
            {
                focused = false;
            }
        }
        else
        {
            focused = false;
        }
    }

    if(focused)
    {
        if(g.GetKey(olc::BACK).bPressed)
        {
            if(text.length() > 0)
                text.erase(text.size()-1);
        }
        if(limit > text.length())
        {
            if(g.GetKey(olc::K0).bPressed) text.push_back('0');
            if(g.GetKey(olc::K1).bPressed) text.push_back('1');
            if(g.GetKey(olc::K2).bPressed) text.push_back('2');
            if(g.GetKey(olc::K3).bPressed) text.push_back('3');
            if(g.GetKey(olc::K4).bPressed) text.push_back('4');
            if(g.GetKey(olc::K5).bPressed) text.push_back('5');
            if(g.GetKey(olc::K6).bPressed) text.push_back('6');
            if(g.GetKey(olc::K7).bPressed) text.push_back('7');
            if(g.GetKey(olc::K8).bPressed) text.push_back('8');
            if(g.GetKey(olc::K9).bPressed) text.push_back('9');
        }

        if(text.length() > 0)
            number = std::stoi(text);
    }
}
