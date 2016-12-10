#ifndef ENTITY_H
#define ENTITY_H
#include "Drawable.h"

/******************************************************************************
Clase base para todas las entidades del juego.
*******************************************************************************/

class Entity: public Drawable
{
    public:
        Entity();
        virtual ~Entity();
        virtual void render();
        virtual void update();

    protected:

    private:
};

#endif // ENTITY_H
