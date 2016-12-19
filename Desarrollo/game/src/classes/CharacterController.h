#ifndef CHARACTER_H
#define CHARACTER_H

#include "DrawableReplica.h"

class CharacterController : public dwn::DrawableReplica
{
    public:
        CharacterController();
        virtual ~CharacterController();


        int getStrength();
        void setStrength(int s);
        int getHealth();
        void setHealth(int h);

        virtual void readEvents();

        float getSpeedX();
        float getSpeedZ();

    protected:

    private:
        const float _speedRun = 20.f;
        const float _speedWalk = 5.f;

        int m_strength;
        int m_health;

        float m_speedX;
        float m_speedZ;
};

#endif // CHARACTER_H
