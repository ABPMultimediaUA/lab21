#ifndef TRIGGERCONSUMABLE_H
#define TRIGGERCONSUMABLE_H

#include "Trigger.h"

class Consumable;

class TriggerConsumable : public Trigger
{
    public:

        TriggerConsumable(Consumable* owner);

        virtual ~TriggerConsumable();

        void Update();

        void SetSensor();

        void onBeginContact(EntityPhysics* otherObject);

        void onEndContact(EntityPhysics* otherObject);

    protected:

    private:

        Consumable* m_owner;
        bool m_touchingMainPlayer;
};

#endif // TRIGGERCONSUMABLE_H
