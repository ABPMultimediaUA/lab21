#include "Trigger.h"

Trigger::Trigger() :
    ToBeRemoved(false)
{
    // Parametros de fisicas
    m_isSensor = true;
    setClassID(EntityPhysics::trigger_id);
}

Trigger::~Trigger()
{

}

void Trigger::SetToBeRemoved()
{
    ToBeRemoved = true;
}

bool Trigger::IsToBeRemoved()
{
    return ToBeRemoved;
}
