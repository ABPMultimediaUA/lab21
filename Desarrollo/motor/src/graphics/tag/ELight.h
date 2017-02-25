#ifndef ELIGHT_H
#define ELIGHT_H

#include "Entity.h"

namespace tag
{
    class ELight : public Entity
    {
        public:
            ELight();
            ~ELight();

            void beginDraw();
            void endDraw();
    };
}

#endif // ELIGHT_H
