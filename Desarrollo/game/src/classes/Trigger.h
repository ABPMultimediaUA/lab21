#ifndef TRIGGER_H
#define TRIGGER_H
#include "Drawable.h"
#include "Entity.h"

/******************************************************************************
Los trigger son los encargados de que se ejecute un evento al ser activados.
Tambien son generados al ocurrir algun evento.
*******************************************************************************/

class Trigger: public Drawable
{
    public:
        Trigger();
        virtual ~Trigger();
        virtual void triggered(Entity* e);

        virtual void render();
        void update();


    protected:

    private:

};

#endif // TRIGGER_H
