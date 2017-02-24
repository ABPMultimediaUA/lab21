#ifndef ECAMERA_H
#define ECAMERA_H

#include "Entity.h"


namespace dwe
{
    class ECamera : public Entity
    {
        public:
            ECamera();
            ~ECamera();

            void beginDraw();
            void endDraw();
    };
}

#endif // ECAMERA_H
