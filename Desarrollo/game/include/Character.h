#ifndef CHARACTER_H
#define CHARACTER_H

#include "Drawable.h"

class Character : public Drawable
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
