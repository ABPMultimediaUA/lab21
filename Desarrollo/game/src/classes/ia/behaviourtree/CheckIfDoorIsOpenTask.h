#ifndef CHECKIFDOORISOPENTASK_H
#define CHECKIFDOORISOPENTASK_H

#include <iostream>

#include "Door.h"
#include "Node.h"



using namespace std;


class CheckIfDoorIsOpenTask : public Node
{
    public:

        CheckIfDoorIsOpenTask(Door* d);

        virtual ~CheckIfDoorIsOpenTask();

        virtual States run();

    protected:

    private:

        Door* door;
};

#endif // CHECKIFDOORISOPENTASK_H
