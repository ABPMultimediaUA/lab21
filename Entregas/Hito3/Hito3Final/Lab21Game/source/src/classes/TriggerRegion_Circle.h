#ifndef TRIGGERREGION_CIRCLE_H
#define TRIGGERREGION_CIRCLE_H
#include "TriggerRegion.h"

class TriggerRegion_Circle: public TriggerRegion
{
    public:
        TriggerRegion_Circle(dwe::vec2f c, double r):center(c), radius(r){}
        bool isTouching(dwe::vec2f EntityPos)const
        {
            return ((EntityPos.x - center.x)^2 + (EntityPos.y - center.y)^2 <= radius^2);
        }

    private:
        dwe::vec2f center;
        double radius;
};

#endif // TRIGGERREGION_CIRCLE_H
