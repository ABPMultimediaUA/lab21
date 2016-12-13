#ifndef CHARACTER_H
#define CHARACTER_H

#include "EntityPhysics.h"

class CharacterController : public EntityPhysics
{
    public:
        CharacterController();
        virtual ~CharacterController();


        int getStrength();
        void setStrength(int s);
        int getHealth();
        void setHealth(int h);

    protected:

    private:
        int m_strength;
        int m_health;
};

#endif // CHARACTER_H
