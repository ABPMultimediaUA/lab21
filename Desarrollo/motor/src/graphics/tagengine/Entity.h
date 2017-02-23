#ifndef ENTITY_H
#define ENTITY_H

#include <string>

namespace dwe
{
    class Entity
    {
        public:
            Entity();
            virtual ~Entity();

            std::string m_cadena;

            virtual void beginDraw() = 0;
            virtual void endDraw() = 0;

        protected:

        private:
    };
}

#endif // ENTITY_H
