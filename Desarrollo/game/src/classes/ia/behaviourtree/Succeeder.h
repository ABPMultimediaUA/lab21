#ifndef SUCCEEDER_H
#define SUCCEEDER_H

#include "Node.h"

class Succeeder : public Node
{
    public:

        Succeeder();

        virtual ~Succeeder();

        void addChild (Node* ch);

        States run();

    protected:

    private:

        Node* child;
};

#endif // SUCCEEDER_H
