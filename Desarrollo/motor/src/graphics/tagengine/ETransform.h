#ifndef ETRANSFORM_H
#define ETRANSFORM_H

#include "Entity.h"

#include <glm/glm.hpp>

#include "GraphicsEngine.h"

#include "EntitiesAttributes.h"

namespace dwe
{
    class ETransform : public Entity
    {
        public:
            ETransform();
            ~ETransform();

            void identity();
            void load(glm::mat4 m);
            void traspose();

            void translate(vec3f t);
            void translate(float x, float y, float z);

            void rotate(vec3f r);
            void rotate(float x, float y, float z);

            void scale(vec3f s);
            void scale(float x, float y, float z);

            void beginDraw();
            void endDraw();

            glm::mat4 getMatrix();

        private:
            glm::mat4   m_matrix;

    };
}

#endif // ETRANSFORM_H
