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
        void setSpeedBoost();
        void dash();


    protected:

    private:
        static const float _speedRun = 50.f;
        static const float _speedWalk = 10.f;
        static const float _speedDash = 400.f;
        static const float _maxSpeedBostTime = 5000.0;
        static const float _maxEvadingTime = 1000.0;

        int m_strength;
        int m_health;

        float m_speedX;
        float m_speedZ;
        float m_t;


        bool m_hasSpeedBoost;
        float m_timeSpeedBost;
        bool m_isEvading;
        float m_timeEvading;

};

#endif // CHARACTER_H
