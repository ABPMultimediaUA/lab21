#ifndef TRIGGER_H
#define TRIGGER_H

#include "EntityPhysics.h"

/******************************************************************************
Los trigger son los encargados de que se ejecute un evento al ser activados.
Tambien son generados al ocurrir algun evento.
*******************************************************************************/

class Trigger: public EntityPhysics
{
    public:

        Trigger();

        virtual ~Trigger();

        virtual void Update() = 0;

        void SetToBeRemoved();

        bool IsToBeRemoved();

    protected:

        bool ToBeRemoved;

    private:

};

#endif // TRIGGER_H
