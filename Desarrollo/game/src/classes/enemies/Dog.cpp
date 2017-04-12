#include "Dog.h"

Dog::Dog()
{
    steps = 2000;
    //set up state machine
    d_pStateMachine = new StateMachine<Dog>(this);

    d_pStateMachine->SetCurrentState(DAsleepState::Instance());

}

Dog::~Dog()
{
    delete d_pStateMachine;
}

StateMachine<Dog>* Dog::GetFSM()const
{
    return d_pStateMachine;
}

int Dog::getSteps ()
{
    return steps;
}

void Dog::setSteps (int s)
{
    steps = s;
}

void Dog::update()
{
    steps--;
    d_pStateMachine->Update();
}

void Dog::render()
{

}

