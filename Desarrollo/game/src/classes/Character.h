#ifndef CHARACTER_H
#define CHARACTER_H

#include "DrawableReplica.h"

class Character : public dwn::DrawableReplica
{
    public:
        Character();
        virtual ~Character();


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
