#ifndef GAME_H
#define GAME_H

#include <vector>
#include "GraphicsEngine.h"

class Projectile;

class Scene
{
    public:
        Scene();
        virtual ~Scene();

        void createProjectile(dwe::vec3f origin, float angle);
        void deleteProjectile(unsigned int i);
        void updateProjectiles();

        void createSpeedBoost(int i, Player* p, float px, float py, float pz);
        void updateSpeedBoosts();

    protected:

    private:
        std::vector<Projectile*> m_projectiles;
        std::vector<SpeedBoost*> m_speedBoosts;
};

#endif // GAME_H
