#ifndef DOG_H
#define DOG_H

#include <Enemy.h>
#include <StateMachine.h>
#include <DogStates.h>
#include <iostream>


class Dog : public Enemy
{
    public:
        Dog();

        ~Dog();

        StateMachine<Dog>* GetFSM()const;

        void Update();

        int getSteps();


    protected:

    private:
        int steps;
        StateMachine<Dog>*  d_pStateMachine;
};

#endif // DOG_H
