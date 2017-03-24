#ifndef TRIGGER_H
#define TRIGGER_H

#include "Drawable.h"
#include "Entity.h"
#include "EntityPhysics.h"

/******************************************************************************
Los trigger son los encargados de que se ejecute un evento al ser activados.
Tambien son generados al ocurrir algun evento.
*******************************************************************************/

class Trigger: public Drawable, public EntityPhysics
{
    public:
        Trigger();
        virtual ~Trigger();
        virtual void triggered(Entity* e);

        virtual void render();
        void update();

        virtual void setNode(dwe::Node* n);
        virtual void setPosition(dwe::vec3f p);

        virtual void onBeginContact(EntityPhysics* otherObject);
        virtual void onEndContact(EntityPhysics* otherObject);

    protected:
        bool m_touchingMainPlayer;

    private:

};

#endif // TRIGGER_H
