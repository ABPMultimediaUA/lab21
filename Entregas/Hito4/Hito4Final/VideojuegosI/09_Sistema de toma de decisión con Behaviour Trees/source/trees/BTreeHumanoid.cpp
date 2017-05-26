#include "BTreeHumanoid.h"
#include "Sequence.h"
#include "Selector.h"
#include "Succeeder.h"
#include "PerceptionTask.h"
#include "AttackRangeCondition.h"
#include "AttackTask.h"
#include "MemoryCondition.h"
#include "PatrolCondition.h"
#include "ElapsedTimeCondition.h"
#include "PathplanningTask.h"
#include "MoveTask.h"

BTreeHumanoid::BTreeHumanoid(Enemy* owner)
{
    m_owner = owner;

    seqRoot = new Sequence();
        taskPerception = new PerceptionTask(owner);
        selAct = new Selector();
            seqAttack = new Sequence();
                condAttackRange = new AttackRangeCondition(owner);
                succAttack = new Succeeder();
                    seqAttack2 = new Sequence();
                        condAttackElapsed = new ElapsedTimeCondition(owner, 1.0f);
                        taskAttack = new AttackTask(owner);
            seqMove = new Sequence();
                succPlanPath = new Succeeder();
                    seqPlanPath = new Sequence();
                        succMemory = new Succeeder();
                            selMemory = new Selector();
                                condMemory = new MemoryCondition(owner);
                                condPatrol = new PatrolCondition(owner);
                        //condElapsedTime = new ElapsedTimeCondition(owner, 1.0f);
                        taskPathplanning = new PathplanningTask(owner);
                taskMove = new MoveTask(owner);

    root = seqRoot;

    seqRoot->addChild(taskPerception);
    seqRoot->addChild(selAct);
        selAct->addChild(seqAttack);
            seqAttack->addChild(condAttackRange);
            seqAttack->addChild(succAttack);
                succAttack->addChild(seqAttack2);
                    seqAttack2->addChild(condAttackElapsed);
                    seqAttack2->addChild(taskAttack);
        selAct->addChild(seqMove);
            seqMove->addChild(succPlanPath);
                succPlanPath->addChild(seqPlanPath);
                    seqPlanPath->addChild(succMemory);
                        succMemory->addChild(selMemory);
                            selMemory->addChild(condMemory);
                            selMemory->addChild(condPatrol);
                    //seqPlanPath->addChild(condElapsedTime);
                    seqPlanPath->addChild(taskPathplanning);
            seqMove->addChild(taskMove);

}

BTreeHumanoid::~BTreeHumanoid()
{
    delete seqRoot;
    delete taskPerception;
    delete selAct;
    delete seqAttack;
    delete condAttackRange;
    delete taskAttack;
    delete seqMove;
    delete succPlanPath;
    delete seqPlanPath;
    delete succMemory;
    delete selMemory;
    delete condMemory;
    delete condPatrol;
    //delete condElapsedTime;
    delete taskPathplanning;
    delete taskMove;
}
