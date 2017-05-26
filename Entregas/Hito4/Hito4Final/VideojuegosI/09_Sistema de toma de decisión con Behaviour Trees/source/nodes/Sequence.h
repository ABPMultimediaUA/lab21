#ifndef SEQUENCE_H
#define SEQUENCE_H
#include "CompositeNode.h"


class Sequence: public CompositeNode
{
    public:
        Sequence();
        virtual ~Sequence();
        virtual States run();

    protected:

    private:
};

#endif // SEQUENCE_H
