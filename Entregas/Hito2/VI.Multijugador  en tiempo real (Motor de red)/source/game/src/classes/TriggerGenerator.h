#ifndef TRIGGERGENERATOR_H
#define TRIGGERGENERATOR_H
#include "Trigger.h"
#include "Generator.h"

class TriggerGenerator: public Trigger
{
    public:
        TriggerGenerator();
        virtual ~TriggerGenerator();
        virtual void
        triggered(Entity *e);

        virtual void render();
        virtual void update();

    protected:

    private:
};

#endif // TRIGGERGENERATOR_H
