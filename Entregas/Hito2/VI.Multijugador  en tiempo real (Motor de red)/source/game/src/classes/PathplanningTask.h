#ifndef PATHPLANNINGTASK_H
#define PATHPLANNINGTASK_H

#include "Node.h"
#include "Pathplanning.h"

class PathplanningTask : public Node
{
    public:

        PathplanningTask(Pathplanning* p, Drawable* pl, Humanoid* h, dwe::Node* n);

        virtual ~PathplanningTask();

        virtual States run();

        void setPlayer(Drawable* pl);

    protected:

    private:

        Pathplanning* path;
        Drawable* play;
        Humanoid* hum;
        dwe::Node* no;
};

#endif // PATHPLANNINGTASK_H
