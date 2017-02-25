#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <glm/glm.hpp>

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

        private:
    };
}

#endif // ENTITY_H
