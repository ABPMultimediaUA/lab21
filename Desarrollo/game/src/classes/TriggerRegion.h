#ifndef TRIGGERREGION_H
#define TRIGGERREGION_H
#include "GraphicsEngine.h"

class TriggerRegion
{
    public:
        virtual ~TriggerRegion(){}
        virtual bool isTouching(dwe::vec2f EntityPos/**, double Entity_radius**/)const = 0;
};

#endif // TRIGGERREGION_H
