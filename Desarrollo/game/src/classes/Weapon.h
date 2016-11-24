#ifndef WEAPON_H
#define WEAPON_H

#include <Drawable.h>


class Weapon : public Drawable
{
    public:
        Weapon();
        virtual ~Weapon();

        virtual void shoot() = 0;


        // Getters & Setters
        int getDamage();
        void setDamage(int damage);

    protected:

    private:
        int m_damage;
};

#endif // WEAPON_H
