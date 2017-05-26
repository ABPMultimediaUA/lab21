#ifndef GRENADEEXPLOSION_H
#define GRENADEEXPLOSION_H

#include "Entity.h"

class GrenadeExplosion: public Entity
{
    public:
        GrenadeExplosion();
        virtual ~GrenadeExplosion();
        virtual void render();
        virtual void update();

        virtual void setNode(dwe::Node* n);   // Necesario para EntityPhysics

        virtual void onBeginContact(EntityPhysics* otherObject);

    protected:

    private:
};

#endif // GRENADEEXPLOSION_H
