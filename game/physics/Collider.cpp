//
// Created by matthewperiut on 10/22/21.
//

#include "Collider.h"

Collider::Collider(v3 position, v3 size) : position(position), size(size)
{
    type = "collider";
}

bool Collider::isColliding(Collider &c)
{
    Collider& a = c;
    Collider& b = *this;

    bool result = true;

    for(int i = 0; i < 3; i++)
    {
        //https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection
        result *= a.min(i) < b.max(i) && a.max(i) > b.min(i);
    }

    return result;
}

float Collider::min(int axis)
{
    switch(axis)
    {
        case 0:
            return position.x;
        case 1:
            return position.y;
        case 2:
            return position.z;
        default:
            return 0;
    }
}

float Collider::max(int axis)
{
    switch(axis)
    {
        case 0:
            return position.x + size.x;
        case 1:
            return position.y + size.y;
        case 2:
            return position.z + size.z;
        default:
            return 0;
    }
}

olc::vf2d Collider::CornerToScreen(bool mx, bool my, bool mz, bool normalized)
{
    v3 mpos = v3(mx ? min(0) : max(0),
                 my ? min(1) : max(1),
                 mz ? min(2) : max(2));
    if(camera != nullptr)
        return mpos.toScreen(*camera);
    else if(normalized)
    {
        v3 holder = position;
        position = v3(0,0,0);
        olc::vf2d result = mpos.toScreenNoCentering();
        position = holder;
        return result;
    }
    else
        return mpos.toScreen(olc::vf2d(0,0));
}

olc::vf2d Collider::GetTopLeft()
{
    return {CornerToScreen(1,0,0).x, CornerToScreen(1,0,1).y};
}

olc::vf2d Collider::GetBottomRight()
{
    return {CornerToScreen(0,0,1).x, CornerToScreen(0,1,0).y};
}

olc::vf2d Collider::Get2DSize()
{
    return GetBottomRight()-GetTopLeft();
}
