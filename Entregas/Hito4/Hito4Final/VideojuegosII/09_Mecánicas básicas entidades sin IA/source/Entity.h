#ifndef ENTITY_H
#define ENTITY_H

#include "DrawablePhysics.h"

/******************************************************************************
Clase base para todas las entidades del juego.
*******************************************************************************/

class Entity: public DrawablePhysics
{
    public:
        Entity();
        virtual ~Entity();
        virtual void render();
        virtual void update();

        void setNetID(unsigned int netID);

    protected:
        unsigned int m_netID;     // Un ID que debe coincidir con el índice array de entidades que se cree. Se envia junto con cualquier mensaje de red

    private:
};

#endif // ENTITY_H
