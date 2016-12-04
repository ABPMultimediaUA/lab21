#include "Legless.h"

Legless::Legless()
{
    crawl = 19;
    //set up state machine
    l_pStateMachine = new StateMachine<Legless>(this);

    l_pStateMachine->SetCurrentState(LPatrolState::Instance());

}

void Legless::Update()
{
    crawl--;
    l_pStateMachine->Update();
}

StateMachine<Legless>* Legless::GetFSM()const
{
    return l_pStateMachine;
}

int Legless::getCrawl ()
{
    return crawl;
}

Legless::~Legless()
{
    delete l_pStateMachine;
}
