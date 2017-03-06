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

        int getCrawl();


    protected:

    private:

        int crawl;

        StateMachine<Legless>*  l_pStateMachine;
};

#endif // LEGLESS_H
