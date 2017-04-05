#ifndef TRIGGERREGION_RECTANGLE_H
#define TRIGGERREGION_RECTANGLE_H
#include "TriggerRegion.h"

class TriggerRegion_Rectangle: public TriggerRegion
{
    public:
        TriggerRegion_Rectangle(dwe::vec2f o, dwe::vec2f wh):TopLeft(o), BottomRight(wh){}
        bool isTouching(dwe::vec2f EntityPos)const
        {
            return (EntityPos.x>TopLeft.x && EntityPos.y>TopLeft.y && EntityPos.x<BottomRight.x && EntityPos.y<BottomRight.y)
        }
    private:
        dwe::vec2f TopLeft;
        dwe::vec2f BottomRight;
};

#endif // TRIGGERREGION_RECTANGLE_H
