#ifndef LEGLESS_H
#define LEGLESS_H

#include <Enemy.h>
#include <StateMachine.h>

class BTreeHumanoid;

class Legless : public Enemy
{
    public:

        Legless();

        ~Legless();

        StateMachine<Legless>* GetFSM()const;

        void update();

        void render(){};

    protected:

    private:

        StateMachine<Legless>*  l_pStateMachine;

        BTreeHumanoid* m_behaviourTree;

};

#endif // LEGLESS_H
