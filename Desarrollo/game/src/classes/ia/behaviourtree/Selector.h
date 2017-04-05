#ifndef SELECTOR_H
#define SELECTOR_H

#include "CompositeNode.h"


class Selector: public CompositeNode
{
    public:
        Selector();
        virtual ~Selector();
        virtual States run();

    protected:

    private:
};

#endif // SELECTOR_H
