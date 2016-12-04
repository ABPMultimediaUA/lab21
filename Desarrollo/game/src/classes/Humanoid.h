#ifndef HUMANOID_H
#define HUMANOID_H

#include <Enemy.h>
#include <StateMachine.h>
#include <HumanoidStates.h>
#include <iostream>


class Humanoid : public Enemy
{
    public:
        Humanoid();

        ~Humanoid();

        StateMachine<Humanoid>* GetFSM()const;

        void Update(); // Update de la maquina de estados

        int getSteps();

        virtual void update() {};

        virtual void render() {};


    protected:

    private:

        int steps;

        StateMachine<Humanoid>*  h_pStateMachine;
};
#endif // HUMANOID_H
