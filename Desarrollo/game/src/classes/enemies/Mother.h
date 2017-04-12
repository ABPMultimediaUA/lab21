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

        virtual void update();
        virtual void render() {};

        int getTimeBetweenCreations();

        void setTimeBetweenCreations(int);

        virtual void setNode(dwe::Node* n);

    protected:

    private:

        int TimeBetweenCreations;
        StateMachine<Mother>*  m_pStateMachine;
};


#endif // MOTHER_H
