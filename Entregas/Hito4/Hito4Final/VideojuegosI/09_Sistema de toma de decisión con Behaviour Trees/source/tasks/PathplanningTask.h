#ifndef PATHPLANNINGTASK_H
#define PATHPLANNINGTASK_H

#include "Node.h"

class Enemy;

class PathplanningTask : public Node
{
    public:

        PathplanningTask(Enemy* owner);

        virtual ~PathplanningTask();

        States run();

    protected:

    private:

        Enemy* m_owner;
};

#endif // PATHPLANNINGTASK_H
