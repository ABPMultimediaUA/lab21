#ifndef PLAYER_H
#define PLAYER_H

#include <defines.h>
#include <CharacterController.h>
#include <vector>
#include <Firearm.h>
#include "EntityPhysics.h"
#include "PlayerMate.h"
#include "NetGame.h"
#include "Gun.h"
#include "Rifle.h"
#include "Shotgun.h"

class Player : public CharacterController, public EntityPhysics
{
    public:
        Player(Gun* gun);
        virtual ~Player();

        void update(){};
        void update(Shotgun* shotgun, Rifle* rifle);
        void render();
        void shoot();
        void throwGrenade();

        virtual void readEvents();


        // Getters & Setters
        virtual void setNode(dwe::Node* n);   // Necesario para EntityPhysics
        int getAmmo(int numWeapon);
        void setAmmo(int numWeapon, int ammount);
        void addAmmo(int numWeapon, int ammount);
        int getGrenades();
        void setGrenades(int n);
        int getHealth();
        int getMaxHealth();
        void setHealth(int n);
        void setMKeys(int id);
        bool getMKey(int n);
        int getNumMedkits();
        void setNumMedkits(int ammount);
        void addMedkits(int ammount);
        void giveMedkits(int ammount, PlayerMate* playermate);
        void receiveMedkits(int ammount);
        void consumeMedkit();
        void giveAmmo(int numWeapon, int ammo, PlayerMate* playermate);
        void receiveAmmo(int numWeapon, int ammo);
        void addWeapon(Consumable* weapon, FirearmKind type);
        bool getHasShotgun();
        bool getHasRifle();
        void swapCurrentWeapon(int w);
        FirearmKind getCurrentWeaponType();
        Firearm* getCurrentWeapon();
        Firearm** getPlayerWeapons();

        virtual const char* getNetObjectID() const;
        virtual void setPosition(dwe::vec3f p);

        virtual void onBeginContact(EntityPhysics* otherObject);

    protected:

    private:
        int         m_ammo[NUM_WEAPONS];
        Firearm*    m_weapons[NUM_WEAPONS];
        int         m_grenades;
        int         m_life;
        bool        m_mKeys[1];
        int         m_medkits;
        float       m_timeMedkit;
        float       m_timeGivingStuff;
        float       m_timeWeaponSwap;
        bool        m_hasGun;
        bool        m_hasShotgun;
        bool        m_hasRifle;
        FirearmKind m_currentWeaponType;
        Firearm*    m_currentWeapon;
        int         m_health;
        int         m_maxHealth;
};

#endif // PLAYER_H
