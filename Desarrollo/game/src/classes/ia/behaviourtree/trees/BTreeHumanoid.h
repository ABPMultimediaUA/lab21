#ifndef BTREEHUMANOID_H
#define BTREEHUMANOID_H

#include "BehaviourTree.h"

class Enemy;

class Sequence;
class Selector;
class Succeeder;
class PerceptionTask;
class AttackRangeCondition;
class AttackTask;
class MemoryCondition;
class PatrolCondition;
class ElapsedTimeCondition;
class PathplanningTask;
class MoveTask;

class BTreeHumanoid : public BehaviourTree
{
    public:

        BTreeHumanoid(Enemy* owner);

        virtual ~BTreeHumanoid();

    protected:

    private:

        Enemy* m_owner;

        Sequence* seqRoot;
            PerceptionTask* taskPerception;
            Selector* selAct;
                Sequence* seqAttack;
                    AttackRangeCondition* condAttackRange;
                    AttackTask* taskAttack;
                Sequence* seqMove;
                    Succeeder* succPlanPath;
                        Sequence* seqPlanPath;
                            Succeeder* succMemory;
                                Selector* selMemory;
                                    MemoryCondition* condMemory;
                                    PatrolCondition* condPatrol;
                            ElapsedTimeCondition* condElapsedTime;
                            PathplanningTask* taskPathplanning;
                    MoveTask* taskMove;
};

#endif // BTREEHUMANOID_H
