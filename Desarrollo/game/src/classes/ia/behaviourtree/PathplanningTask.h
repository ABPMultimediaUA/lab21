#ifndef PATHPLANNINGTASK_H
#define PATHPLANNINGTASK_H

#include "Node.h"

class Pathplanning;
class Enemy;

class PathplanningTask : public Node
{
    public:

        PathplanningTask(Pathplanning* p, Enemy* owner);

        virtual ~PathplanningTask();

        virtual States run();

    protected:

    private:

        Pathplanning* m_pathplanning;
        Enemy* m_owner;
        int time;
};

#endif // PATHPLANNINGTASK_H
