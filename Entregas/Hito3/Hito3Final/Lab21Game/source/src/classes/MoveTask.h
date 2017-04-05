#ifndef MOVETASK_H
#define MOVETASK_H

#include "Node.h"

class Enemy;

class MoveTask : public Node
{
    public:

        MoveTask(Enemy* owner);

        virtual ~MoveTask();

        virtual States run();

    private:

        Enemy* m_owner;
};

#endif // MOVETASK_H
