#include "TriggerSound.h"
#include "Enemy.h"
#include "WorldInstance.h"

TriggerSound::TriggerSound(dwe::vec3f pos, float radius)
{
    setClassID(EntityPhysics::triggerSound_id);
    createCircularBody(pos, radius);
    lastTime = World->getTimeElapsed();
}

TriggerSound::~TriggerSound()
{
    //dtor
}

void TriggerSound::Update()
{
    if(World->getTimeElapsed() - lastTime >= 1.0f/60.0f)
        SetToBeRemoved();
}
