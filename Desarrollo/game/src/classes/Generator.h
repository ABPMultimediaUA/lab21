#ifndef GENERATOR_H
#define GENERATOR_H
#include "Entity.h"
#include "Door.h"

/******************************************************************************
Los generadores se encargan de suministrar energia a las luces y puertas de
una zona que se encuentre desactivada.
*******************************************************************************/

class Generator: public Entity
{
    public:
        Generator(int n, bool b);
        virtual ~Generator();
        void setSector(Entity **s, int e);
        void activateGenerator(); // Activa generador
        virtual void render();
        virtual void update();

    protected:

    private:
        int num;
        bool active;
        int entities; // A cuantas entidades esta relacionado
        Entity **sector; // Array de entidades
};

#endif // GENERATOR_H
