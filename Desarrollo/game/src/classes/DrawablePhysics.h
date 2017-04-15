#ifndef DRAWABLEPHYSICS_H
#define DRAWABLEPHYSICS_H

#include "Drawable.h"
#include "EntityPhysics.h"


class DrawablePhysics : public Drawable, public EntityPhysics
{
    public:
        DrawablePhysics();
        virtual ~DrawablePhysics();

        virtual void setPosition(dwe::vec3f p);

    protected:

    private:
};

#endif // DRAWABLEPHYSICS_H
