#ifndef OPENDOORTASK_H
#define OPENDOORTASK_H

#include <iostream>

#include "Door.h"
#include "Node.h"


using namespace std;

class OpenDoorTask : public Node
{
    public:

        OpenDoorTask(Door* d);

        virtual ~OpenDoorTask();

        virtual States run();

    protected:

    private:

        Door* door;

};

#endif // OPENDOORTASK_H
