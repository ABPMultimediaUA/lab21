#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "GraphicsEngine.h"

#include "NavigationGraph.h"
#include "TriggerSystem.h"

class Enemy;
class Dog;
class Humanoid;
class Guardian;
class Legless;
class Bat;
class Gun;

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

        void createProjectile(dwe::vec3f origin, float angle, std::string weapon, int damage);
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
        void createMagnetKey(int id, float px, float py, float pz);
        void createAmmo(float px, float py, float pz);
        void updateConsumables(Player* mainPlayer);
        NavigationGraph& getNavGraph();
        TriggerSystem& getTriggerSystem();

        Enemy* getClosestEnemy();

        void activeEnemy(uint8_t i);
        void deactiveEnemy(uint8_t i);

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
        Mother* enemyMother;

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

        void createEnemies();
        void updateEnemies();
        void deleteEnemies();
};

#endif // SCENE_H
