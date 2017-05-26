#include "TriggerSystem.h"
#include "Trigger.h"

TriggerSystem::TriggerSystem()
{
    //ctor
}

TriggerSystem::~TriggerSystem()
{
    if(m_triggers.size())
        Destroy();
}

void TriggerSystem::Destroy()
{
    while(m_triggers.size()){
        delete m_triggers.back();
        m_triggers.pop_back();
    }
}

void TriggerSystem::Update()
{
    unsigned int i=0;
    while(i<m_triggers.size())
    {
        Trigger* t = m_triggers[i];
        t->Update();
        if(t->IsToBeRemoved()){
            Remove(i);
        }
        else
            i++;
    }
}

void TriggerSystem::Add(Trigger* newTrigger)
{
    if(newTrigger)
        m_triggers.push_back(newTrigger);
}

void TriggerSystem::Remove(int i)
{
    Trigger* t;
    t = m_triggers.back();
    m_triggers.back() = m_triggers[i];
    m_triggers[i] = t;
    delete m_triggers.back();
    m_triggers.pop_back();
}
