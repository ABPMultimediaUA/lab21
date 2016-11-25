#ifndef FIREARM_H
#define FIREARM_H

#include <defines.h>
#include <Weapon.h>


class Firearm : public Weapon
{
    public:
        Firearm();
        virtual ~Firearm();

        virtual void shoot() = 0;
        virtual void reload() = 0;

        // Getters & setters
        int getCadence();
        void setCadence(int c);
        int getBulletsPerShot();
        void setBulletsPerShot(int b);
        int getClipSize();
        void setClipSize(int c);

    protected:

    private:
        FirearmKind m_kind;
        int m_cadence;
        int m_bulletsPerShot;
        int m_clipSize;
};

#endif // FIREARM_H
