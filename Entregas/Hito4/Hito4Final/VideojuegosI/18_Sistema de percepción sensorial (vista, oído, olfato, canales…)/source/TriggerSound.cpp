#include "TriggerSound.h"
#include "Enemy.h"
#include "WorldInstance.h"

TriggerSound::TriggerSound(dwe::vec3f pos, float radius, bool perma)
{
    setClassID(EntityPhysics::triggerSound_id);
    createCircularBody(pos, radius);
    lastTime = World->getTimeElapsed();
    permanent = perma;
}

TriggerSound::~TriggerSound()
{
    //dtor
}

void TriggerSound::Update()
{
    if(!permanent)
        if(World->getTimeElapsed() - lastTime >= 1.0f/60.0f)
            ToBeRemoved = true;
}
