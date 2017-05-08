#ifndef PATROLCONDITION_H
#define PATROLCONDITION_H

#include "Node.h"

class Enemy;

class PatrolCondition : public Node
{
    public:

        PatrolCondition(Enemy* owner);

        virtual ~PatrolCondition();

        States run();

    protected:

    private:

        Enemy* m_owner;
};

#endif // PATROLCONDITION_H
