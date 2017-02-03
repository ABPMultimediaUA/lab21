#ifndef PATHPLANNING_H
#define PATHPLANNING_H
#include "Drawable.h"
#include "Humanoid.h"





class Pathplanning
{
    public:
        Pathplanning();
        virtual ~Pathplanning();
        void behaviour(Drawable* mainPlayer, Humanoid* enemyHumanoid, dwe::Node* fovnode, bool danyo);//para comportamiento cuando se acerque player

    protected:

    private:
};


#endif
