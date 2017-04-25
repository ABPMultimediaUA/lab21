#ifndef PERCEPTIONTASK_H
#define PERCEPTIONTASK_H

#include "Node.h"

class Enemy;

class PerceptionTask : public Node
{
    public:

        PerceptionTask(Enemy* owner);

        virtual ~PerceptionTask();

        virtual States run();

    protected:

    private:

        Enemy* m_owner;
};

#endif // PERCEPTIONTASK_H
