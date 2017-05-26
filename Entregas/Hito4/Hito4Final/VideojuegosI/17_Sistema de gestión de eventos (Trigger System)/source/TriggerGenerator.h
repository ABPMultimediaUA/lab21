#ifndef TRIGGERGENERATOR_H
#define TRIGGERGENERATOR_H

#include "Trigger.h"

class Generator;

class TriggerGenerator: public Trigger
{
    public:

        TriggerGenerator(Generator* owner);

        virtual ~TriggerGenerator();

        void Update();

        void SetSensor();

        void onBeginContact(EntityPhysics* otherObject);

        void onEndContact(EntityPhysics* otherObject);

    protected:

    private:

        Generator* m_owner;
        bool m_touchingMainPlayer;
};

#endif // TRIGGERGENERATOR_H
