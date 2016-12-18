#ifndef PERCEPTION_H
#define PERCEPTION_H
#include "Player.h"
#include "Humanoid.h"

class Perception
{
    public:
        Perception();
        virtual ~Perception();
        void senses(Player* mainPlayer, Humanoid* enemyHumanoid, dwe::Node* fovnode, float num);

    protected:

    private:
        bool following;

};

#endif // PERCEPTION_H
