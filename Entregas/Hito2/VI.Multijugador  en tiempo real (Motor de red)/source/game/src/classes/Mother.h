#ifndef MOTHER_H
#define MOTHER_H

#include <Enemy.h>
#include <StateMachine.h>
#include <MotherStates.h>
#include <iostream>


class Mother : public Enemy
{
    public:
        Mother();

        ~Mother();

        StateMachine<Mother>* GetFSM()const;

        void Update();

        int getTimeBetweenCreations();

        void setTimeBetweenCreations(int);

    protected:

    private:

        int TimeBetweenCreations;
        StateMachine<Mother>*  m_pStateMachine;
};


#endif // MOTHER_H
