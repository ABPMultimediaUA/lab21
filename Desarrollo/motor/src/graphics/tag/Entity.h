#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <stack>
#include <glm/glm.hpp>
#include <stack>

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

            static glm::mat4 MVmatrix;  // glm la inicializa a entidad
            static std::stack<glm::mat4> TStack;

        private:
    };
}

#endif // ENTITY_H
