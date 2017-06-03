#include "Mother.h"

Mother::Mother()
{

    m_health = 500;
    TimeBetweenCreations = 0;
    //set up state machine
    m_pStateMachine = new StateMachine<Mother>(this);

    m_pStateMachine->SetCurrentState(StillState::Instance());

}


Mother::~Mother()
{
    delete m_pStateMachine;
}

void Mother::update()
{
    //TimeBetweenCreations ++;
    //m_pStateMachine->Update();
}

StateMachine<Mother>* Mother::GetFSM()const
{
    return m_pStateMachine;
}

void Mother::setTimeBetweenCreations (int n)
{
    TimeBetweenCreations = n;
}

int Mother::getTimeBetweenCreations()
{
    return TimeBetweenCreations;
}


/////////////
void Mother::setNode(dwe::Node* n)
{
    Drawable::setNode(n);
    dwe::vec3f box = n->getBoundingBox();
    createStaticBody(getPosition(), box.x, box.z-60);
}
