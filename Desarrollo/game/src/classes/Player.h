#ifndef PLAYER_H
#define PLAYER_H

#include <defines.h>
#include <CharacterController.h>
#include <Firearm.h>
#include "EntityPhysics.h"



class Player : public CharacterController, public EntityPhysics
{
    public:
        Player();
        virtual ~Player();

        void update();
        void render();
        void shoot();
        void throwGrenade();


        // Getters & Setters
        int getAmmo(int numWeapon);
        void setAmmo(int numWeapon, int ammount);
        int getGrenades();
        void setGrenades(int n);

        virtual const char* getNetObjectID() const;
        void setPosition(dwe::vec3f p);

    protected:

    private:
        int         m_ammo[NUM_WEAPONS];
        Firearm*    m_weapons[NUM_WEAPONS];
        int         m_grenades;
};

#endif // PLAYER_H
