#ifndef ECAMERA_H
#define ECAMERA_H

#include "Entity.h"
#include "tag/TAGEngine.h"


namespace tag
{
    class ECamera : public Entity
    {
        public:
            ECamera();
            ~ECamera();

            void beginDraw();
            void endDraw();

            void setPerspective (float fov, float aspect, float near, float far);
            void setParallel (float fov, float aspect, float near, float far);

            void setActive(bool active);

            bool getIfActive();
            bool getIfPerspective();

            glm::mat4 getProjectionMatrix();

        private:

            bool m_isActive;
            bool m_isPerspective;
            float m_nearDistance;
            float m_farDistance;
            glm::mat4 m_projectionMatrix;
    };
}

#endif // ECAMERA_H
