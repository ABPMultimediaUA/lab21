#ifndef FIREARM_H
#define FIREARM_H

#include <defines.h>
#include <Weapon.h>

class Player;

class Firearm : public Weapon
{
    public:
        Firearm();
        virtual ~Firearm();
        int id;
        virtual void shoot(){};
        virtual void reload(){};

        // Getters & setters
        int getCadence();
        void setCadence(int c);
        int getBulletsPerShot();
        void setBulletsPerShot(int b);
        int getClipSize();
        void setClipSize(int c);

        virtual void render() {};
        //virtual void update(Player* mainPlayer);

    protected:

    private:
        FirearmKind m_kind;
        int m_cadence;
        int m_bulletsPerShot;
        int m_clipSize;
};

#endif // FIREARM_H
