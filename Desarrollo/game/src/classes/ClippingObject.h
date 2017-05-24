#ifndef CLIPPINGOBJECT_H
#define CLIPPINGOBJECT_H

#include "Drawable.h"


class ClippingObject : public Drawable
{
    public:
        ClippingObject();
        ~ClippingObject();   // No para heredar

        virtual void update() {};
        virtual void render() {};

        void setPosClipping(dwe::vec3f p);
        dwe::vec3f getPosClipping();
    protected:

    private:
        dwe::vec3f m_posClipping;
};

#endif // CLIPPINGOBJECT_H
