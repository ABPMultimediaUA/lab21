#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "GraphicsEngine.h"

#include "TriggerDoor.h"
#include "TriggerGenerator.h"
#include "Door.h"
#include "Generator.h"
#include "MagnetKey.h"
#include "Gun.h"

#define NUM_ENTITIES 3

class Projectile;
class Consumable;
class Firearm;


class Scene
{
    public:

        static Scene* Instance();

        Scene();
        virtual ~Scene();

        void Init();

        void Update();


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

        Entity *entities[NUM_ENTITIES]; // Array de entidades
        Entity *sector[1]; // Sector no funcional que se le asigna a un generador
        Trigger *triggers[3]; // Triggers
        bool llaveCogida;
        Player* mainPlayer;
        Gun* gun;

        std::vector<Projectile*> m_projectiles;
        std::vector<Consumable*> m_consumables;
};

#endif // SCENE_H
