#ifndef ENTITIESATTRIBUTES_H
#define ENTITIESATTRIBUTES_H

#include "Entity.h"
#include <glm/glm.hpp>
#include <stack>

namespace dwe
{
    class EntitiesAttributes : public Entity
    {
        public:
            EntitiesAttributes();
            virtual ~EntitiesAttributes();

            static std::stack<glm::mat4> m_stack;
            static glm::mat4 m_ModelViewMatrix;

        protected:

        private:


    };

}


#endif // ENTITIESATTRIBUTES_H
