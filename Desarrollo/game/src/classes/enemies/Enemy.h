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

        virtual void update();

        float getSpeed();

        void setNetID(unsigned int netID);

        void move();
        bool Sense();
        void Hear(dwe::vec3f pos);
        void SetClosestPlayer(Drawable* closest);
        void SetInAttackRange(bool b);
        bool IsInAttackRange();
        bool Attack();  //Devuelve true mientras esta a mitad del ataque, y false cuando termina
        void PlanPath();
        bool RouteEnd();
        void SetMemory(bool b);
        bool HasMemory();
        void SetMemoryPosition(dwe::vec2f memory);
        dwe::vec2f GetMemoryPosition();
        void SetTargetPosition(dwe::vec2f target);

        virtual void setNode(dwe::Node* n);   // Necesario para EntityPhysics
        virtual void onBeginContact(EntityPhysics* otherObject);

        int getHealth();
        void resetHealth();
        int getDist2Player();

        void activeEnemy(dwe::vec3f position);
        void deactiveEnemy();

    protected:
        float m_speed;              // Velocidad: hay que actualizarla en el constructor de cada enemigo
        unsigned int m_netID;       // Un ID que debe coincidir con el índice array de entidades que se cree. Se envia junto con cualquier mensaje de red
        int m_maxHealth;
        int m_health;
        int m_attackPower;

        bool attackRange;
        bool attacking;
        float attackTime;
        bool attackTriggered;
        bool memory;
        dwe::vec2f memoryPosition;
        dwe::vec2f targetPosition;  //Siguiente lugar al que va a dirigirse. Se usa para darle una posición al pathplanning. Cambiará en función de a quién perseguir o a dónde ir
        Drawable* closestPlayer;

        Perception* m_perception;
        Pathplanning* m_pathplanning;

    private:
};

#endif // ENEMY_H
