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

        int getSteps();

        void setSteps(int s);

        virtual void update();

        virtual void render();

    protected:

    private:

        int steps;

        StateMachine<Legless>*  l_pStateMachine;
};

#endif // LEGLESS_H
