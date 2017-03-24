#ifndef PERCEPTION_H
#define PERCEPTION_H
#include "Player.h"

class Humanoid;
class PathplanningTask;

class Perception
{
    public:
        Perception();
        virtual ~Perception();
        bool senses(Player* mainPlayer, Humanoid* enemyHumanoid, PathplanningTask* p);

    protected:

    private:
        bool following;

};

#endif // PERCEPTION_H
