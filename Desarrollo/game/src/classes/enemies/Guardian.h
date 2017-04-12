#ifndef GUARDIAN_H
#define GUARDIAN_H

#include <Enemy.h>
#include <StateMachine.h>
#include <GuardianStates.h>
#include <iostream>


class Guardian : public Enemy
{
    public:
        Guardian();

        ~Guardian();

        StateMachine<Guardian>* GetFSM()const;

        int getSteps();

        void setSteps(int s);

        virtual void update();

        virtual void render();

    protected:

    private:

        int steps;

        StateMachine<Guardian>*  g_pStateMachine;
};

#endif // GUARDIAN_H
