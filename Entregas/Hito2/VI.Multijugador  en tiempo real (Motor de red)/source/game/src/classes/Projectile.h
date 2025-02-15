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
        Projectile(dwe::vec3f origin, float angle); // Proyectil creado por player
        //Projectile(int *origin, int *destiny); // Proyectil creado por enemigos
        virtual ~Projectile();
        bool getCollides();
        virtual void render();
        virtual void update();

        virtual void setNode(dwe::Node* n);   // Necesario para EntityPhysics

        virtual void onBeginContact(EntityPhysics* otherObject);

    protected:

    private:
        static const float _velocity = 85.f;

        dwe::vec3f position;
        int speed;
        float angle;
        bool collides;

};

#endif // PROJECTILE_H
