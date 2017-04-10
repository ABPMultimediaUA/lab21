#ifndef PLAYER_H
#define PLAYER_H

#include <defines.h>
#include <CharacterController.h>
#include <vector>
#include "EntityPhysics.h"
#include "PlayerMate.h"
#include "NetGame.h"
#include "Gun.h"
#include "Rifle.h"
#include "Shotgun.h"
#include "Grenade.h"

class Firearm;

class Player : public CharacterController, public EntityPhysics
{
    public:
        Player(Gun* gun);
        virtual ~Player();

        void update(){};
        void update(Shotgun* shotgun, Rifle* rifle);
        void render();

        /// \brief Dispara el arma actual
        /// \details Tiene en cuenta si el tiempo que ha pasado es el correcto segun la
        /// cadencia del arma activa.
        /// \return Devuelve si ha podido disparar o no
        bool shoot(float timeSinceLastShoot);

        void throwGrenade();

        virtual void readEvents();


        // Getters & Setters
        virtual void setNode(dwe::Node* n);   // Necesario para EntityPhysics
        void addAmmo(int numWeapon, int ammount);
        int getGrenades();
        void setGrenades(int n);
        int getHealth();
        int getMaxHealth();
        void setHealth(int n);
        void setMKeys(int id);
        bool getMKey(int n);
        void addSpeedBoost();
        int getNumMedkits();
        void setNumMedkits(int ammount);
        void addMedkits(int ammount);
        void giveMedkits(int ammount, PlayerMate* playermate);
        void receiveMedkits(int ammount);
        void consumeMedkit();
        void consumeSpeedBoost();
        void giveAmmo(int numWeapon, int ammo, PlayerMate* playermate);
        void receiveAmmo(int numWeapon, int ammo);
        void addWeapon(Consumable* weapon, FirearmKind type);
        bool getHasShotgun();
        bool getHasRifle();
        void swapCurrentWeapon(int w);
        FirearmKind getCurrentWeaponType();
        Firearm* getCurrentWeapon();
        Firearm** getPlayerWeapons();
        Weapon* getPlayerGun();
        Weapon* getPlayerShotgun();
        Weapon* getPlayerRifle();

        virtual const char* getNetObjectID() const;
        virtual void setPosition(dwe::vec3f p);
        /***/
        void sayPosition();
        /***/

        virtual void onBeginContact(EntityPhysics* otherObject);

    protected:

    private:
        //int         m_ammo[NUM_WEAPONS];
        Firearm*    m_weapons[NUM_WEAPONS];
        int         m_grenades;
        int         m_life;
        bool        m_mKeys[3];
        int         m_medkits;
        int         m_speedBoosts;
        float       m_timeMedkit;
        float       m_timeToSpeedBoost;
        float       m_timeGivingStuff;
        float       m_timeWeaponSwap;
        bool        m_hasGun;
        bool        m_hasShotgun;
        bool        m_hasRifle;
        FirearmKind m_currentWeaponType;
        Firearm*    m_currentWeapon;
        int         m_health;
        int         m_maxHealth;
        Grenade     m_grenadeWeapon;

};

#endif // PLAYER_H
