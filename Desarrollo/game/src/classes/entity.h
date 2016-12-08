#ifndef ENTITY_H
#define ENTITY_H

/******************************************************************************
Clase base para todas las entidades del juego.
*******************************************************************************/

class entity
{
    public:
        entity();
        virtual ~entity();
        virtual void render();
        virtual void update();

    protected:

    private:
};

#endif // ENTITY_H
