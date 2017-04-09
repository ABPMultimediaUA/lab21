
#include "Humanoid.h"
#include "Pathplanning.h"
#include "Perception.h"
#include "Selector.h"
#include "Sequence.h"
#include "PathplanningTask.h"
#include "PerceptionTask.h"
#include "MoveTask.h"
#include <cmath>

Humanoid::Humanoid()
{
    m_speed = 2.0; // m/s

    //set up state machine
    //h_pStateMachine = new StateMachine<Humanoid>(this);

    //h_pStateMachine->SetCurrentState(HPatrolState::Instance());

    m_perception = new Perception(this);
    m_pathplanning = new Pathplanning(this);

    /******** BEHAVIOUR TREE ********/
    /**** Special nodes ****/
    selector1 = new Selector;
    sequence1 = new Sequence;

    /**** Tasks ****/
    perc = new PerceptionTask(this);
    path = new PathplanningTask(this);
    movetask = new MoveTask(this);

    //patrol = new PatrolTask(this);

    /**** Creating the tree ****/

    selector1->addChild(sequence1);
    //selector1->addChild(patrol);

    sequence1->addChild(perc);
    sequence1->addChild(path);
    sequence1->addChild(movetask);

    targetPosition = dwe::vec2f(0,0);

}

/*void Humanoid::Update()
{
    h_pStateMachine->Update();
}*/

void Humanoid::update()
{
    selector1->run();
}

/*void Humanoid::move()
{
    Enemy::move();
}*/

/*StateMachine<Humanoid>* Humanoid::GetFSM()const
{
    return h_pStateMachine;
}*/

Humanoid::~Humanoid()
{
    //delete h_pStateMachine;
    delete m_perception;
    delete m_pathplanning;
    delete selector1;
    delete sequence1;
    delete path;
    delete movetask;
    //delete perc;
    //delete patrol;
    //delete fovnode;
}
