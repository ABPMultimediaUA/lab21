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

        int getSteps();

        void setSteps(int s);

        virtual void update();

        virtual void render();

    protected:

    private:

        int steps;

        StateMachine<Bat>*  b_pStateMachine;
};

#endif // BAT_H
