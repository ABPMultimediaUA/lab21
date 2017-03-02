#ifndef ELIGHT_H
#define ELIGHT_H

#include "Entity.h"
#include "tag/TAGEngine.h"

namespace tag
{
    class ELight : public Entity
    {
        public:
            ELight();
            ~ELight();

            void beginDraw();
            void endDraw();

            GLfloat getIntensity();
            void setIntensity(GLfloat intensity);

        private:

            GLfloat m_intensity;

    };
}

#endif // ELIGHT_H
