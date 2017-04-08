#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "GraphicsEngine.h"

#include "Dog.h"
#include "Humanoid.h"
#include "Guardian.h"
#include "Legless.h"
#include "Bat.h"

#include "TriggerDoor.h"
#include "TriggerGenerator.h"
#include "Door.h"
#include "Generator.h"
#include "MagnetKey.h"
#include "Gun.h"

#include "NavigationGraph.h"

class Projectile;
class ProjectileGrenade;
class Consumable;
class Firearm;


class Scene
{
    public:

        static Scene* Instance();

        Scene();
        virtual ~Scene();

        void Init();
        void Destroy();

        void Update();

        void closestEnemy(Player* mainPlayer, Enemy* enemy);

        int getNumberEnemies(); /** Control fin de juego */

        void createProjectile(dwe::vec3f origin, float angle, std::string weapon);
        void deleteProjectile(unsigned int i);
        void updateProjectiles();

        void createProjectileGrenade(dwe::vec3f origin, float angle);
        void deleteProjectileGrenade(unsigned int i);
        void updateProjectilesGrenade();

        void createEnemyHumanoid(dwe::vec3f origin, float angle);

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
        NavigationGraph& getNavGraph();

        Enemy* getClosestEnemy();

    protected:

    private:

        MagnetKey *llave;
        bool llaveCogida;

        // NPcs
        Player* mainPlayer;
        Humanoid* enemyHumanoid;
        Dog* enemyDog;
        Bat* enemyBat;
        Guardian* enemyGuardian;
        Legless* enemyLegless;
        /**/

        Firearm* weapon;

        // Objets
        Gun* gun;
        Shotgun* shotgun;
        Rifle* rifle;
        Medkit* medkit;

        bool a;

        std::vector<Projectile*> m_projectiles;
        std::vector<ProjectileGrenade*> m_projectilesGrenades;
        std::vector<Consumable*> m_consumables;
        std::vector<Enemy*> m_enemies;

        NavigationGraph navGraph;

        float timeLastProjectil;


        int moreEnemiesX;
        int moreEnemiesZ;

        // Random
        dwe::Node* joint_try;
        EntityPhysics* bjoint;
};

#endif // SCENE_H
