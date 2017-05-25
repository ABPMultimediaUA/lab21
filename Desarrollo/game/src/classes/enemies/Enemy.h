#ifndef ENEMY_H
#define ENEMY_H

#include "DrawablePhysics.h"

class TriggerVision;
class Perception;
class Pathplanning;

class Enemy : public DrawablePhysics
{
    public:
        Enemy();

        void SetVision();

        virtual ~Enemy();

        virtual void update();

        float getSpeed();

        void setNetID(unsigned int netID);

        void move();
        bool Sense();
        void Hear(dwe::vec3f pos);
        void SeePlayer(dwe::vec3f pos);
        void SetClosestPlayer(Drawable* closest);
        void SetInAttackRange(bool b);
        bool IsInAttackRange();
        bool Attack();  //Devuelve true mientras esta a mitad del ataque, y false cuando termina
        void PlanPath();
        bool RouteEnd();
        void ClearRoute();
        void SetMemory(bool b);
        bool HasMemory();
        void SetMemoryPosition(dwe::vec2f memory);
        dwe::vec2f GetMemoryPosition();

        void SetHearing(bool b);
        void SetSeeing(bool b);
        void SetSoundPosition(dwe::vec2f sound);
        void SetVisionPosition(dwe::vec2f vision);
        bool GetHearing();
        bool GetSeeing();
        dwe::vec2f GetSoundPosition();
        dwe::vec2f GetVisionPosition();

        void ChangePatrol();
        void SetPatrolPosition(dwe::vec2f patrol);
        dwe::vec2f GetPatrolPosition();
        void SetTargetPosition(dwe::vec2f target);
        dwe::vec2f GetTargetPosition();
        void SetPatrolPoints(dwe::vec2f p1, dwe::vec2f p2);

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
        dwe::vec2f patrol1;
        dwe::vec2f patrol2;
        dwe::vec2f currentPatrol;
        Drawable* closestPlayer;
        TriggerVision* m_triggerVision;

        Perception* m_perception;
        Pathplanning* m_pathplanning;

    private:
};

#endif // ENEMY_H
