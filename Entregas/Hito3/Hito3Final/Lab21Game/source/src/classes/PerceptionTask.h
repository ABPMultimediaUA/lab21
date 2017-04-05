#ifndef PERCEPTIONTASK_H
#define PERCEPTIONTASK_H

#include "Node.h"
#include "GraphicsEngine.h"

class Perception;
class Humanoid;
class PathplanningTask;

class PerceptionTask : public Node
{
    public:

        PerceptionTask(Perception* p, Humanoid* h, /*dwe::Node* n, */PathplanningTask* pa);

        virtual ~PerceptionTask();

        virtual States run();

    protected:

    private:

        Perception* per;
        Player* play;
        Humanoid* hum;
        //dwe::Node* no;
        PathplanningTask* path;
};

#endif // PERCEPTIONTASK_H
