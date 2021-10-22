//
// Created by matthewperiut on 10/22/21.
//

#include "Draw.h"
#include "../physics/Box.h"

void draw(Collider& collider)
{
    if(collider.type == "collider")
    {
        for(int i = 0; i < 12; i++)
        {
            CurrentEngine->DrawLine(collider.CornerToScreen(box[i][0][0],box[i][0][1],box[i][0][2]),
                                    collider.CornerToScreen(box[i][1][0],box[i][1][1],box[i][1][2]));
        }
    }
    if(collider.type == "collider_decal")
    {
        CurrentEngine->DrawDecal(collider.GetTopLeft(), reinterpret_cast<olc::Decal*>(collider.ptr[0]));
    }
}