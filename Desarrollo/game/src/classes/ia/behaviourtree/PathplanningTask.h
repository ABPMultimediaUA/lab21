#ifndef PATHPLANNINGTASK_H
#define PATHPLANNINGTASK_H

#include "Node.h"

class Enemy;

class PathplanningTask : public Node
{
    public:

        PathplanningTask(Enemy* owner);

        virtual ~PathplanningTask();

        virtual States run();

    protected:

    private:

        Enemy* m_owner;
        float lastTime;
};

#endif // PATHPLANNINGTASK_H
