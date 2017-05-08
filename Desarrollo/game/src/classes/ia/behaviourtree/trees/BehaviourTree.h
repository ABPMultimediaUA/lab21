#ifndef BEHAVIOURTREE_H
#define BEHAVIOURTREE_H

#include "CompositeNode.h"

class BehaviourTree
{
    public:

        BehaviourTree(){};

        virtual ~BehaviourTree(){};

        void Run(){root->run();};

    protected:

        CompositeNode* root;

    private:

};

#endif // BEHAVIOURTREE_H
