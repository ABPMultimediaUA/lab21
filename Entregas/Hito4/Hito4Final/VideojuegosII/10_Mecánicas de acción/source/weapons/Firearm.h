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

        // Getters & setters
        float getCadence();
        int getBulletsPerShot();
        void setBulletsPerShot(int b);
        int getClipSize();
        void setClipSize(int c);

        virtual void render() {};

        virtual void setPut() = 0;   // Enfundada
        virtual void setDraw() = 0;  // Desenfundada

    protected:
        float m_cadence;
        FirearmKind m_kind;
        int m_bulletsPerShot;
        int m_clipSize;

};

#endif // FIREARM_H
