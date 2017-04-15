#ifndef PROJECTILEGRENADE_H
#define PROJECTILEGRENADE_H

#include "Entity.h"
#include "EntityPhysics.h"

/******************************************************************************
Los proyectiles son los elementos que viajan de una posicion a otra del espacio
y haran una funcion diferente dependiendo del tipo de proyectil que sea.
*******************************************************************************/

class ProjectileGrenade: public Entity
{
    public:
        ProjectileGrenade();
        ProjectileGrenade(dwe::vec3f origin, float angle); // Proyectil creado por player
        void init();
        virtual ~ProjectileGrenade();
        bool getCollides();
        virtual void render();
        virtual void update();

        virtual void setNode(dwe::Node* n);   // Necesario para EntityPhysics

        virtual void onBeginContact(EntityPhysics* otherObject);

        virtual void setPosition(dwe::vec3f p);

    protected:

    private:
        static const float _impulse = 0.3;

        dwe::vec3f  m_position;
        int         m_speed;
        float       m_angle;
        bool        m_collides;

};

#endif // PROJECTILE_H
