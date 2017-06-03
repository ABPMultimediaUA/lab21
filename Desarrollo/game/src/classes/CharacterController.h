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

        bool getIsEvading();


    protected:

    private:
        static constexpr float _speedRun            = 4.f;  // en m/s
        static constexpr float _speedWalk           = 2.f;
        static constexpr float _speedDash           = 1.5f;  //multiplicador
        static constexpr float _maxSpeedBoostTime   = 5.0;  // en segundos
        static constexpr float _maxEvadingTime      = 1.0;  // en segundos

        int m_strength;
        int m_health;

        float m_speedX;
        float m_speedZ;
        float m_t;


        bool m_hasSpeedBoost;
        float m_timeSpeedBoost;
        bool m_isEvading;
        float m_timeEvading;

};

#endif // CHARACTER_H
