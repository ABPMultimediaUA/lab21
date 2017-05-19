#ifndef GUARDIAN_H
#define GUARDIAN_H

#include <Enemy.h>
#include <StateMachine.h>

#include "Enemy.h"

class BTreeHumanoid;

class Guardian : public Enemy
{
    public:
        Guardian();

        ~Guardian();

        StateMachine<Guardian>* GetFSM()const;

        virtual void update();

        virtual void render();

    protected:

    private:

        StateMachine<Guardian>*  g_pStateMachine;

        BTreeHumanoid* m_behaviourTree;
};

#endif // GUARDIAN_H
