#ifndef PATROLTASK_H
#define PATROLTASK_H

#include "Node.h"
#include "Humanoid.h"

class PatrolTask : public Node
{
    public:

        PatrolTask(Humanoid* h, dwe::Node* n);

        virtual ~PatrolTask();

        virtual States run();

    protected:

    private:

        Humanoid* hum;
        dwe::Node* no;
        float pos1;
        float pos2;
        bool dir;
};

#endif // PATROLTASK_H
