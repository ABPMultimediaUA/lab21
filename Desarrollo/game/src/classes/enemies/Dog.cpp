#include "Dog.h"

Dog::Dog()
{
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

void Dog::update()
{
    //d_pStateMachine->Update();
}

void Dog::render()
{

}

