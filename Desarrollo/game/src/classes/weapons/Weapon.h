#ifndef WEAPON_H
#define WEAPON_H

#include <Drawable.h>

class Player;

class Weapon : public Drawable
{
    public:
        Weapon();
        virtual ~Weapon();

        virtual void shoot() = 0;

        bool getIsTaken();
        void update(){};
        void take();   // Marca como ya cogido y quita nodo como en update
        void setNetID(unsigned int netID);

        // Getters & Setters
        int getDamage();
        void setDamage(int damage);
        int getAmmo();
        void setAmmo(int ammo);
        void addAmmo(int ammo);

    protected:
        int m_netID;
    private:
        int m_damage;
        bool m_isTaken;
        int m_ammo;

};

#endif // WEAPON_H
