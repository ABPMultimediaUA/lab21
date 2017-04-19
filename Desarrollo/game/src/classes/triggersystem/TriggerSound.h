#ifndef TRIGGERSOUND_H
#define TRIGGERSOUND_H

#include "Trigger.h"
#include "GraphicsEngine.h"

class Enemy;

class TriggerSound : public Trigger
{
    public:

        TriggerSound(dwe::vec3f pos, float radius);

        virtual ~TriggerSound();

        void Update(){};

    protected:

    private:
};

#endif // TRIGGERSOUND_H
