#ifndef NODE_H
#define NODE_H

#include "NodeStates.h"

class Node
{
   public:
        Node();
        virtual ~Node();
        virtual States run();
        bool getRunning();

    protected:
        bool brunning;

};

#endif // NODE_H
