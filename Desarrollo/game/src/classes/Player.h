#ifndef PLAYER_H
#define PLAYER_H

#include <defines.h>
#include <CharacterController.h>
#include <vector>
#include "PlayerMate.h"
#include "NetGame.h"
#include "Gun.h"
#include "Rifle.h"
#include "Shotgun.h"
#include "Grenade.h"

class Firearm;
class TriggerSound;

class Player : public CharacterController
{
    public:
        Player();
        virtual ~Player();

        void update();
        void render();

        /// \brief Dispara el arma actual
        /// \details Tiene en cuenta si el tiempo que ha pasado es el correcto segun la
        /// cadencia del arma activa.
        /// \return Devuelve si ha podido disparar o no
        bool shoot(float timeSinceLastShoot);

        /// \brief Lanza una granada
        void throwGrenade();

        /// \brief Pregunta si puede lanzar una granada
        /// \details Tiene en cuenta si el tiempo que ha pasado es el correcto segun la
        /// cadencia de la granada y si tenemos granadas.
        /// \return Devuelve si puede disparar o no
        bool canThrowGrenade(float timeSinceLastGrenade);

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
        int getSpeedBoosts();
        int getNumMedkits();
        void setNumMedkits(int ammount);
        void addMedkits(int ammount);
        void giveMedkits(int ammount, PlayerMate* playermate);
        void receiveMedkits(int ammount);
        void consumeMedkit();
        void consumeSpeedBoost();
        void giveAmmo(int numWeapon, int ammo, PlayerMate* playermate);
        void receiveAmmo(int numWeapon, int ammo);
        void takeDamage(int damage);
        void swapCurrentWeapon(FirearmKind weaponKind);
        FirearmKind getCurrentWeaponType();
        Firearm* getCurrentWeapon();
        Firearm** getPlayerWeapons();
        Weapon* getPlayerGun();
        Weapon* getPlayerShotgun();
        Weapon* getPlayerRifle();
        ///////////
        bool reloadWeapon();

        virtual const char* getNetObjectID() const;

        void sayPosition();

        void addWeapon(FirearmKind type);

        virtual void onBeginContact(EntityPhysics* otherObject);

    protected:

    private:
        static const float _changeOffsetTime        = 0.2;
        static const float _reloadOffsetTime        = 2.0;
        static const float _takeDamageOffsetTime    = 0.5;
        static const float _throwGrenadeOffsetTime  = 0.5;
        struct TPlayerWeaponKey {
            EKEY_CODE   key;
            FirearmKind weapon;
        };
        TPlayerWeaponKey m_playerWeaponKey[eNumWeapons];

        Firearm*    m_weapons[eNumWeapons];
        int         m_grenades;
        int         m_life;
        bool        m_mKeys[4];
        int         m_medkits;
        int         m_speedBoosts;
        float       m_lastTimeTakeDamage;
        float       m_timeMedkit;
        float       m_timeToSpeedBoost;
        float       m_timeGivingStuff;
        float       m_timeWeaponSwap;
        float       m_timeReload;
        float       m_timeLastProjectil;
        float       m_timeLastGrenade;      // Cuando ha terminado de lanzar granada
        float       m_timeInitGrenade;      // Cuando ha empezado a lanzar granada
        bool        m_isThrowingGrenade;    // Esta lanzando granada
        bool        m_grenadeSound;
        FirearmKind m_currentWeaponType;
        Firearm*    m_currentWeapon;
        int         m_health;
        int         m_maxHealth;
        Grenade     m_grenadeWeapon;
        TriggerSound* m_soundTrigger;

        bool        m_localIsEvading;

        void deleteWeapons();
        void setSoundTrigger();
};

#endif // PLAYER_H
