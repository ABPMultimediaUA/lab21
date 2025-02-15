#ifndef PERCEPTION_H
#define PERCEPTION_H
#include "Player.h"
#include "Humanoid.h"
#include "PathplanningTask.h"

class Perception
{
    public:
        Perception();
        virtual ~Perception();
        bool senses(Player* mainPlayer, Humanoid* enemyHumanoid, dwe::Node* fovnode, PathplanningTask* p);

    protected:

    private:
        bool following;

};

#endif // PERCEPTION_H
