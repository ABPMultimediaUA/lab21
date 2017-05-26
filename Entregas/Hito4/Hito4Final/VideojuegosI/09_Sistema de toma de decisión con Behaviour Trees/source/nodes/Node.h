#ifndef NODE_H
#define NODE_H

#include "NodeStates.h"

class Node
{
   public:

        Node(){};

        virtual ~Node(){};

        virtual States run(){return success;};

        bool getRunning(){return brunning;};

    protected:

        bool brunning;

};

#endif // NODE_H
