#ifndef TRIGGERSOUND_H
#define TRIGGERSOUND_H

#include "Trigger.h"
#include "GraphicsEngine.h"

class Enemy;

class TriggerSound : public Trigger
{
    public:

        TriggerSound(dwe::vec3f pos, float radius, bool perma);

        virtual ~TriggerSound();

        void Update();

    protected:

    private:

        float lastTime;
        bool permanent;
};

#endif // TRIGGERSOUND_H
