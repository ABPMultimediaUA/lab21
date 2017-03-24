#ifndef TAG_ECAMERA_H
#define TAG_ECAMERA_H

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
            vec3f getBoundingBox() { return vec3f(0,0,0); };

            void setPerspective (float fov, float aspect, float near, float far);
            void setParallel (float fov, float aspect, float near, float far);

            void setActive(bool active);

            bool getIfActive();
            bool getIfPerspective();

            glm::mat4 getProjectionMatrix();

        private:

            bool m_isActive;
            bool m_isPerspective;
            //float m_nearDistance;
            //float m_farDistance;
            glm::mat4 m_projectionMatrix;
    };
}

#endif // TAG_ECAMERA_H
