#ifndef BAT_H
#define BAT_H

#include <Enemy.h>
#include <StateMachine.h>
#include <BatStates.h>
#include <iostream>


class Bat : public Enemy
{
    public:
        Bat();

        ~Bat();

        StateMachine<Bat>* GetFSM()const;

        void Update();

        int getStepstoalarm();


    protected:

    private:
        int stepstoalarm;
        StateMachine<Bat>*  b_pStateMachine;
};

#endif // BAT_H
