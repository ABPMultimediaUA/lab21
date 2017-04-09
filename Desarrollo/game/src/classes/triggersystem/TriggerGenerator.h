#ifndef TRIGGERGENERATOR_H
#define TRIGGERGENERATOR_H
#include "Trigger.h"
#include "Generator.h"

class TriggerGenerator: public Trigger
{
    public:
        TriggerGenerator();
        virtual ~TriggerGenerator();
        virtual void triggered(Generator *g);

        virtual void render();
        void update(Generator *g);

    protected:

    private:
};

#endif // TRIGGERGENERATOR_H
