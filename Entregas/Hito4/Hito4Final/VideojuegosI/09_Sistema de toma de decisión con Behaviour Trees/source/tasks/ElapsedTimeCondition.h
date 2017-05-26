#ifndef ELAPSEDTIMECONDITION_H
#define ELAPSEDTIMECONDITION_H

#include "Node.h"

class Enemy;

class ElapsedTimeCondition : public Node
{
    public:

        ElapsedTimeCondition(Enemy* owner, float time);

        virtual ~ElapsedTimeCondition();

        States run();

    protected:

    private:

        Enemy* m_owner;
        float waitTime;
        float lastTime;
};

#endif // ELAPSEDTIMECONDITION_H
