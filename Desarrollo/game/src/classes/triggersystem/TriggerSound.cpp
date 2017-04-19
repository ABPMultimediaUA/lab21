#include "TriggerSound.h"
#include "Enemy.h"

TriggerSound::TriggerSound(dwe::vec3f pos, float radius)
{
    setClassID(EntityPhysics::triggerSound_id);
    createCircularBody(pos, radius);
}

TriggerSound::~TriggerSound()
{
    //dtor
}
