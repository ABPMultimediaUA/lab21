#include "Legless.h"
#include "LeglessStates.h"
#include "Pathplanning.h"
#include "Perception.h"
#include "Selector.h"
#include "Sequence.h"
#include "PathplanningTask.h"
#include "PerceptionTask.h"
#include "MoveTask.h"

Legless::Legless()
{
    //set up state machine
    l_pStateMachine = new StateMachine<Legless>(this);

    l_pStateMachine->SetCurrentState(LPatrolState::Instance());

    m_speed = 2.0; // m/s

    m_perception = new Perception(this);
    m_pathplanning = new Pathplanning(this);

    selector1 = new Selector;
    sequence1 = new Sequence;

    perc = new PerceptionTask(this);
    path = new PathplanningTask(this);
    movetask = new MoveTask(this);

    //patrol = new PatrolTask(this);

    ////// Creating the tree //////

    selector1->addChild(sequence1);
    //selector1->addChild(patrol);

    sequence1->addChild(perc);
    sequence1->addChild(path);
    sequence1->addChild(movetask);

    targetPosition = dwe::vec2f(0,0);

}

StateMachine<Legless>* Legless::GetFSM()const
{
    return l_pStateMachine;
}

void Legless::update()
{
    l_pStateMachine->Update();
    selector1->run();
}

Legless::~Legless()
{
    delete m_perception;
    delete m_pathplanning;
    delete selector1;
    delete sequence1;
    delete path;
    delete movetask;
    delete perc;
    delete l_pStateMachine;
}
