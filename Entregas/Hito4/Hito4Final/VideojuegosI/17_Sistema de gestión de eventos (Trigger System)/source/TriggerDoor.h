#ifndef TRIGGERDOOR_H
#define TRIGGERDOOR_H

#include "Trigger.h"

class Door;

class TriggerDoor: public Trigger
{
    public:

        TriggerDoor(Door* owner);

        virtual ~TriggerDoor();

        void Update();

        void SetSensor();

        void onBeginContact(EntityPhysics* otherObject);

        void onEndContact(EntityPhysics* otherObject);

    protected:

    private:

        Door* m_owner;
        bool m_touchingMainPlayer;
};

#endif // TRIGGERDOOR_H
