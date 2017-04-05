#ifndef WALKTHROUGHDOORTASK_H
#define WALKTHROUGHDOORTASK_H

#include <iostream>

#include "Door.h"
#include "Node.h"
#include "Humanoid.h"



using namespace std;

class WalkThroughDoorTask : public Node
{
    public:

        WalkThroughDoorTask(Humanoid* n, Door* d);

        virtual ~WalkThroughDoorTask();

        virtual States run();

    protected:

    private:

        Humanoid* npc;
        Door* door;


};

#endif // WALKTHROUGHDOORTASK_H
