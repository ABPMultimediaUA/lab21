#ifndef TRIGGERGENERATOR_H
#define TRIGGERGENERATOR_H
#include "Trigger.h"

class TriggerGenerator: public Trigger
{
    public:
        TriggerGenerator();
        virtual ~TriggerGenerator();
        virtual void
        triggered(Entity *e);

        virtual void render();
        void update(Entity *e);

    protected:

    private:
};

#endif // TRIGGERGENERATOR_H
