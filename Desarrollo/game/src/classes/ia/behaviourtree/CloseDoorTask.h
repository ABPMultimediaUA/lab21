#ifndef CLOSEDOORTASK_H
#define CLOSEDOORTASK_H

#include <iostream>

#include "Door.h"
#include "Node.h"



using namespace std;

class CloseDoorTask : public Node
{
    public:

        CloseDoorTask(Door* d);

        virtual ~CloseDoorTask();

        virtual States run();


    protected:

    private:

        Door* door;
};

#endif // CLOSEDOORTASK_H
