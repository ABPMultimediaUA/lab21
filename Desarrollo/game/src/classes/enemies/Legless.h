#ifndef LEGLESS_H
#define LEGLESS_H

#include <Enemy.h>
#include <StateMachine.h>
#include <iostream>

class Selector;
class Sequence;
class PathplanningTask;
class PerceptionTask;
class MoveTask;

class Legless : public Enemy
{
    public:

        Legless();

        ~Legless();

        StateMachine<Legless>* GetFSM()const;

        void Update();

        void update();

        void render(){};

    protected:

    private:

        StateMachine<Legless>*  l_pStateMachine;

        Selector* selector1;
        Sequence *sequence1;

        PathplanningTask* path;
        PerceptionTask* perc;

        MoveTask* movetask;
};

#endif // LEGLESS_H
