#include "Humanoid.h"
#include "Pathplanning.h"
#include "Perception.h"
#include "Selector.h"
#include "Sequence.h"
#include "PathplanningTask.h"
#include "PerceptionTask.h"
#include "PatrolTask.h"

Humanoid::Humanoid()
{
    steps = 19;
    m_speed = 0.1;

    //set up state machine
    h_pStateMachine = new StateMachine<Humanoid>(this);

    h_pStateMachine->SetCurrentState(HPatrolState::Instance());

    //Creación fov
    //fovnode = GEInstance->createNode("media/fov");
    //fovnode->setMaterialFlag(EMF_WIREFRAME, true);
    //fovnode->setPosition(getPosition());
    //fovnode->setRotation(getRotation());
    percep = new Perception();
    pathp = new Pathplanning();
    /**** Special nodes ****/
    selector1 = new Selector;
    sequence1 = new Sequence;
    /**** Tasks ****/
    path = new PathplanningTask(pathp, this/*, fovnode*/);
    perc = new PerceptionTask(percep, this, /*fovnode,*/ path);
    patrol = new PatrolTask(this, fovnode);
    /**** Creating the tree ****/

    selector1->addChild(sequence1);
    selector1->addChild(patrol);

    sequence1->addChild(perc);
    sequence1->addChild(path);

}

void Humanoid::Update()
{
    steps--;
    h_pStateMachine->Update();
}

void Humanoid::update()
{
    selector1->run();
}

StateMachine<Humanoid>* Humanoid::GetFSM()const
{
    return h_pStateMachine;
}

int Humanoid::getSteps ()
{
    return steps;
}

Humanoid::~Humanoid()
{
    delete h_pStateMachine;
    delete percep;
    delete pathp;
    delete selector1;
    delete sequence1;
    delete path;
    delete perc;
    delete patrol;
    //delete fovnode;
}
