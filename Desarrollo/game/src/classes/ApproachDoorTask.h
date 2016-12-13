#ifndef APPROACHDOORTASK_H
#define APPROACHDOORTASK_H

#include <iostream>

#include "Node.h"
#include "Humanoid.h"
#include "Door.h"


using namespace std;

class ApproachDoorTask : public Node
{
    public:

        ApproachDoorTask(Humanoid* n, Door* d);

        virtual ~ApproachDoorTask();

        virtual States run();

    protected:

    private:


        Humanoid* npc;
        Door* door;


};

#endif // APPROACHDOORTASK_H
