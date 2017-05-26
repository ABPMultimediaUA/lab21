#ifndef ATTACKRANGECONDITION_H
#define ATTACKRANGECONDITION_H

#include "Node.h"

class Enemy;

class AttackRangeCondition : public Node
{
    public:

        AttackRangeCondition(Enemy* owner);

        virtual ~AttackRangeCondition();

        States run();

    protected:

    private:

        Enemy* m_owner;
};

#endif // ATTACKRANGECONDITION_H
