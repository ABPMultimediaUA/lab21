#ifndef GENERATOR_H
#define GENERATOR_H
#include "Entity.h"
#include "Door.h"
#include "EntityPhysics.h"

/******************************************************************************
Los generadores se encargan de suministrar energia a las luces y puertas de
una zona que se encuentre desactivada.
*******************************************************************************/

class Generator: public Entity, public EntityPhysics
{
    public:
        Generator(int n, bool b);
        virtual ~Generator();
        void setSector(Entity **s, int e);
        void activateGenerator(); // Activa generador
        virtual void render();
        virtual void update();

        virtual void setNode(dwe::Node* n);
        virtual void setPosition(dwe::vec3f p);

    protected:

    private:
        int num;
        bool active;
        int entities; // A cuantas entidades esta relacionado
        Entity **sector; // Array de entidades
};

#endif // GENERATOR_H
