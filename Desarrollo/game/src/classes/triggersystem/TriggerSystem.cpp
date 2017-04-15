#include "TriggerSystem.h"
#include "Trigger.h"

TriggerSystem::TriggerSystem()
{
    //ctor
}

TriggerSystem::~TriggerSystem()
{
    while(m_triggers.size())
        m_triggers.pop_back();
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
            i--;
        }
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
    m_triggers.pop_back();
}
