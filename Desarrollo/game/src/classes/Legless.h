#ifndef LEGLESS_H
#define LEGLESS_H

#include <Enemy.h>
#include <StateMachine.h>
#include <LeglessStates.h>
#include <iostream>


class Legless : public Enemy
{
    public:
        Legless();

        ~Legless();

        StateMachine<Legless>* GetFSM()const;

        void Update();

    protected:

    private:

        StateMachine<Legless>*  l_pStateMachine;

        //Pathfinding

        //Perception
};

#endif // LEGLESS_H
