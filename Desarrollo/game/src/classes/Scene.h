#ifndef GAME_H
#define GAME_H

#include <vector>
#include "GraphicsEngine.h"

class Projectile;
class Consumable;
class Firearm;


class Scene
{
    public:
        Scene();
        virtual ~Scene();

        void createProjectile(dwe::vec3f origin, float angle);
        void deleteProjectile(unsigned int i);
        void updateProjectiles();

        void createSpeedBoost(float px, float py, float pz);
        void createMedkit(float px, float py, float pz);
        void createCShotgun(float px, float py, float pz);
        void createCRifle(float px, float py, float pz);
        Gun* createGun(float px, float py, float pz);
        Shotgun* createShotgun(float px, float py, float pz);
        Rifle* createRifle(float px, float py, float pz);
        void createAmmoGun(float px, float py, float pz);
        void updateConsumables(Player* mainPlayer);
        void updatePlayerWeapons(Player* mainPlayer, Firearm** weapons);

    protected:

    private:
        std::vector<Projectile*> m_projectiles;
        std::vector<Consumable*> m_consumables;
};

#endif // GAME_H
