#ifndef TRIGGERDOOR_H
#define TRIGGERDOOR_H
#include "Trigger.h"
#include "Door.h"

class TriggerDoor: public Trigger
{
    public:
        TriggerDoor();
        virtual ~TriggerDoor();
        virtual void triggered(Entity *e);

        virtual void render();
        void update(Entity *e);

    protected:

    private:
};

#endif // TRIGGERDOOR_H
