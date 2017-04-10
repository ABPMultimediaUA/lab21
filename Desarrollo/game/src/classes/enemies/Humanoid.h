#ifndef HUMANOID_H
#define HUMANOID_H

#include "Enemy.h"

class Selector;
class Sequence;
class PathplanningTask;
class PerceptionTask;
class MoveTask;

class Humanoid : public Enemy
{
    public:

        Humanoid();

        ~Humanoid();

        void update();

        void render(){};

    protected:

    private:

        Selector* selector1;
        Sequence *sequence1;

        PathplanningTask* path;
        PerceptionTask* perc;

        MoveTask* movetask;

        //PatrolTask* patrol;

};
#endif // HUMANOID_H
