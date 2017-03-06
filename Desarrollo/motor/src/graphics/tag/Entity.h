#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <stack>
#include <glm/glm.hpp>
#include <stack>

#include "tag/ResourceManager.h"

namespace tag
{
    class Entity
    {
        public:
            Entity();
            virtual ~Entity();

            std::string m_cadena;  // TODO para pruebas de recorrido, quitar

            virtual void beginDraw() = 0;
            virtual void endDraw() = 0;

            static glm::mat4 modelMatrix;  // glm la inicializa a entidad
            static glm::mat4 viewMatrix;  // glm la inicializa a entidad
            static std::stack<glm::mat4> TStack;
            static ResourceManager resourceManager;

        private:
    };
}

#endif // ENTITY_H
