#ifndef TAG_ETRANSFORM_H
#define TAG_ETRANSFORM_H

#include "Entity.h"

#include <glm/glm.hpp>

#include "tag/Types.h"

namespace tag
{
    class ETransform : public Entity
    {
        public:
            ETransform();
            ~ETransform();

            void identity();
            void load(glm::mat4 m);
            void transpose();

            void translate(vec3f t);
            void translate(float x, float y, float z);

            void rotate(vec3f r);
            void rotate(float x, float y, float z);

            void scale(vec3f s);
            void scale(float x, float y, float z);

            void beginDraw();
            void endDraw();
            vec3f getBoundingBox() { return vec3f(0,0,0); };

            glm::mat4 getMatrix();

        private:
            glm::mat4   m_matrix;

    };
}

#endif // TAG_ETRANSFORM_H
