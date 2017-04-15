#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "GraphicsEngine.h"

#include "Dog.h"
#include "Humanoid.h"
#include "Guardian.h"
#include "Legless.h"
#include "Bat.h"

#include "Gun.h"

#include "NavigationGraph.h"
#include "TriggerSystem.h"

class Projectile;
class ProjectileGrenade;
class Consumable;
class Firearm;

struct TEnemy
{
    bool active;
    Enemy* enemy;

    TEnemy() : active(true), enemy(0) {};
};


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
        void createMagnetKey(int id, float px, float py, float pz);
        Shotgun* createShotgun(float px, float py, float pz);
        Rifle* createRifle(float px, float py, float pz);
        void createAmmoGun(float px, float py, float pz);
        void updateConsumables(Player* mainPlayer);
        void updatePlayerWeapons(Player* mainPlayer, Firearm** weapons);
        NavigationGraph& getNavGraph();
        TriggerSystem& getTriggerSystem();

        Enemy* getClosestEnemy();

    protected:

    private:
        TEnemy* m_enemies;
        uint8_t m_numEnemies;
        uint8_t m_numActiveEnemies;
        float   m_timeLastEnemyActive;   // Tiempo de la última activación de un enemigo
        float   m_timeEnemyActive;       // Tiempo que pasa entre activaciones de enemigos
        uint8_t m_moreEnemiesX;
        uint8_t m_moreEnemiesZ;

        dwe::vec3f m_posMother;

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

        bool a;

        std::vector<Projectile*> m_projectiles;
        std::vector<ProjectileGrenade*> m_projectilesGrenades;
        std::vector<Consumable*> m_consumables;
        //std::vector<Enemy*> m_enemies;

        NavigationGraph navGraph;
        TriggerSystem m_triggerSystem;

        float timeLastProjectil;



        // Random
        dwe::Node* joint_try;
        EntityPhysics* bjoint;

        void createEnemies();
        void updateEnemies();
        void deleteEnemies();
};

#endif // SCENE_H
