#include "Bat.h"

Bat::Bat()
{
    stepstoalarm = 19;
    //set up state machine
    b_pStateMachine = new StateMachine<Bat>(this);

    b_pStateMachine->SetCurrentState(BPatrolState::Instance());

}

void Bat::Update()
{
    stepstoalarm--;
    b_pStateMachine->Update();
}

StateMachine<Bat>* Bat::GetFSM()const
{
    return b_pStateMachine;
}

int Bat::getStepstoalarm ()
{
    return stepstoalarm;
}

Bat::~Bat()
{
    delete b_pStateMachine;
}
