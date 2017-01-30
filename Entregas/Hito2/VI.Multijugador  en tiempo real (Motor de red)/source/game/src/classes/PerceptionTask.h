#ifndef PERCEPTIONTASK_H
#define PERCEPTIONTASK_H

//#include "Node.h"
#include "Perception.h"
#include "PathplanningTask.h"

class PerceptionTask : public Node
{
    public:

        PerceptionTask(Perception* p, Player* pl, Humanoid* h, dwe::Node* n, PathplanningTask* pa);

        virtual ~PerceptionTask();

        virtual States run();

    protected:

    private:

        Perception* per;
        Player* play;
        Humanoid* hum;
        dwe::Node* no;
        PathplanningTask* path;
};

#endif // PERCEPTIONTASK_H
