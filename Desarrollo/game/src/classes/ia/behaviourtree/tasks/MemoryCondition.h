#ifndef MEMORYCONDITION_H
#define MEMORYCONDITION_H

#include "Node.h"

class Enemy;

class MemoryCondition : public Node
{
    public:

        MemoryCondition(Enemy* owner);

        virtual ~MemoryCondition();

        States run();

    protected:

    private:

        Enemy* m_owner;
        bool checked;
};

#endif // MEMORYCONDITION_H
