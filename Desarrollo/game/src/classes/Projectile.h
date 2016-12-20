#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"
#include "EntityPhysics.h"

/******************************************************************************
Los proyectiles son los elementos que viajan de una posicion a otra del espacio
y haran una funcion diferente dependiendo del tipo de proyectil que sea.
*******************************************************************************/

class Projectile: public Entity, public EntityPhysics
{
    public:
        Projectile();
        Projectile(int *origin, float angle); // Proyectil creado por player
        Projectile(int *origin, int *destiny); // Proyectil creado por enemigos
        virtual ~Projectile();
        void moveProjectile();
        bool getCollides();
        double* getPosition();
        virtual void render();
        virtual void update();

        virtual void setNode(dwe::Node* n);   // Necesario para EntityPhysics

        virtual void onBeginContact(EntityPhysics* otherObject);

    protected:

    private:
        double position[2];
        int speed;
        float angle;
        bool collides;
        int contador;// para quitar, por ahora el disparo dura x veces    rmm
};

#endif // PROJECTILE_H
