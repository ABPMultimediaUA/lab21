#ifndef ENEMY_H
#define ENEMY_H

#include "Drawable.h"
#include "EntityPhysics.h"

class Perception;
class Pathplanning;

class Enemy : public Drawable, public EntityPhysics
{
    public:
        Enemy();
        virtual ~Enemy();

        float getSpeed();

        void setNetID(unsigned int netID);

        virtual void setPosition(dwe::vec3f p);
        virtual void move();
        virtual void setNode(dwe::Node* n);   // Necesario para EntityPhysics�
        virtual void onBeginContact(EntityPhysics* otherObject);

        int getHealth();
        int getDist2Player();

    protected:
        float m_speed;              // Velocidad: hay que actualizarla en el constructor de cada enemigo
        unsigned int m_netID;       // Un ID que debe coincidir con el �ndice array de entidades que se cree. Se envia junto con cualquier mensaje de red
        int m_health;

        Perception* m_perception;
        Pathplanning* m_pathplanning;

    private:
};

#endif // ENEMY_H
