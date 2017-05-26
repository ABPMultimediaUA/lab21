#ifndef ATTACKTASK_H
#define ATTACKTASK_H

#include "Node.h"

class Enemy;

class AttackTask : public Node
{
    public:

        AttackTask(Enemy* owner);

        virtual ~AttackTask();

        States run();

    protected:

    private:

        Enemy* m_owner;
};

#endif // ATTACKTASK_H
