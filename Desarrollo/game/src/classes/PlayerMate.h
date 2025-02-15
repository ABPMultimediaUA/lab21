#ifndef PLAYERMATE_H
#define PLAYERMATE_H

#include "DrawableReplica.h"
#include "GraphicsEngine.h"
#include "Player.h"
#include "Firearm.h"

class TriggerSound;


class PlayerMate : public dwn::DrawableReplica
{
    public:
        PlayerMate();
        virtual ~PlayerMate();

        virtual void update();
        virtual void render();

        // Getters, Setters
        virtual void setNode(dwe::Node* n);   // Necesario para EntityPhysics
        virtual dwe::vec3f getShift();
        virtual void setShift(dwe::vec3f s);
        virtual unsigned short int getHealth();
        virtual void setHealth(unsigned short int h);
        virtual unsigned short int getNumGrenades();
        virtual void setNumGrenades(unsigned short int n);
        virtual unsigned short int getNumMedkits();
        virtual void setNumMedkits(unsigned short int n);
        virtual void addMedkits(unsigned short int n);
        virtual void giveMedkits(int ammount);
        virtual void giveAmmo(int numWeapon, int ammount);

        void setWeapon(uint8_t index, Firearm* firearm);
        void swapCurrentWeapon(FirearmKind firearmKind);

        void setAnimation(dwe::AnimationType a);


    protected:

    private:
        static const uint8_t _maxWeapons = 3;

        dwe::vec3f          m_shift; // Desplazamiento respecto del movimiento anterior
        unsigned short int  m_health;
        unsigned short int  m_numGrenades;
        unsigned short int  m_numMedkits;
        FirearmKind         m_currentWeaponKind;
        Firearm*            m_weapons[_maxWeapons];
        TriggerSound*       m_soundTrigger;

        void setSoundTrigger();
};

#endif // PLAYERMATE_H
