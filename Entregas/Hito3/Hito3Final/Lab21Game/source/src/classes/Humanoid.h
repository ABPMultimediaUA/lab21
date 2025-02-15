#ifndef HUMANOID_H
#define HUMANOID_H

#include <Enemy.h>
#include <StateMachine.h>
#include <HumanoidStates.h>
#include <iostream>
#include <list>

class Perception;
class Pathplanning;
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

        virtual void render() {};

        void move();


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
