#ifndef SCENARYELEMENT_H
#define SCENARYELEMENT_H

#include "DrawablePhysics.h"

class ScenaryElement : public DrawablePhysics
{
    public:
        ScenaryElement();
        virtual ~ScenaryElement();

        void update();
        void render();

        virtual void setNode(dwe::Node* n);

    protected:

    private:
        int rotationY;
};

#endif // SCENARYELEMENT_H
