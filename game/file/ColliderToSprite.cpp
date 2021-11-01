//
// Created by matthewperiut on 10/24/21.
//

#include "ColliderToSprite.h"
#include "../physics/Box.h"
#include "DrawToSprite.h"

olc::Sprite* CreateSpriteDebugDraw(Collider& collider, olc::Pixel outlineColor)
{

    olc::vf2d sprSize = collider.Get2DSize();
    auto* colliderSprite = new olc::Sprite(sprSize.x+1, sprSize.y+1);
    for(int i = 0; i < colliderSprite->width; i++)
    {
        for(int j = 0; j < colliderSprite->height; j++)
        {
            colliderSprite->SetPixel(i,j,olc::BLANK);
        }
    }

    // Temporary fix for strange negative behavior in CornerOnScreenNormalized()
    //olc::vi2d adjustment = olc::vi2d(0,collider.CornerToScreen(box[0][1][0],box[0][1][1],box[0][1][2],true).y);

    olc::vf2d topLeft = collider.GetTopLeft();
    for(int i = 0; i < 12; i++)
    {
        DrawLineToSprite(collider.CornerToScreen(box[i][0][0],box[i][0][1],box[i][0][2]) - topLeft,
                         collider.CornerToScreen(box[i][1][0],box[i][1][1],box[i][1][2]) - topLeft, outlineColor, *colliderSprite);

    }

    /*
    vi2d min{0,0};
    vi2d max{colliderSprite->width-1,colliderSprite->height-1};
    DrawLineToSprite(vi2d(min.x,min.y),vi2d(min.x,max.y), outlineColor, *colliderSprite);
    DrawLineToSprite(vi2d(min.x,min.y),vi2d(max.x,min.y), outlineColor, *colliderSprite);
    DrawLineToSprite(vi2d(max.x,max.y),vi2d(max.x,min.y), outlineColor, *colliderSprite);
    DrawLineToSprite(vi2d(max.x,max.y),vi2d(min.x,max.y), outlineColor, *colliderSprite);
    */

    return colliderSprite;
}