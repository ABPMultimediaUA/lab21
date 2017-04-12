#ifndef ENEMY_H
#define ENEMY_H

#include "DrawablePhysics.h"

class Perception;
class Pathplanning;

class Enemy : public DrawablePhysics
{
    public:
        Enemy();
        virtual ~Enemy();

        float getSpeed();

        void setNetID(unsigned int netID);

        virtual void setPosition(dwe::vec3f p);
        void move();
        bool Sense();
        void PlanPath();
        void SetTargetPosition(dwe::vec2f target);

        virtual void setNode(dwe::Node* n);   // Necesario para EntityPhysicsç
        virtual void onBeginContact(EntityPhysics* otherObject);

        int getHealth();
        void resetHealth();
        int getDist2Player();

    protected:
        float m_speed;              // Velocidad: hay que actualizarla en el constructor de cada enemigo
        unsigned int m_netID;       // Un ID que debe coincidir con el índice array de entidades que se cree. Se envia junto con cualquier mensaje de red
        int m_maxHealth;
        int m_health;

        dwe::vec2f targetPosition;  //Siguiente lugar al que va a dirigirse. Se usa para darle una posición al pathplanning. Cambiará en función de a quién perseguir o a dónde ir

        Perception* m_perception;
        Pathplanning* m_pathplanning;

    private:
};

#endif // ENEMY_H
