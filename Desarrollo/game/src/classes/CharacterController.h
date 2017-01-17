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

        void setSpeed(bool &a, bool &b);
        bool getSpeedBoost();



    protected:

    private:
        static const float _speedRun = 20.f;
        static const float _speedWalk = 5.f;

        int m_strength;
        int m_health;

        float m_speedX;
        float m_speedZ;
        float m_t;


        bool m_speedb;
};

#endif // CHARACTER_H
