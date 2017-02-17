#ifndef SCENARYELEMENT_H
#define SCENARYELEMENT_H

#include "Drawable.h"
#include "EntityPhysics.h"


class ScenaryElement : public Drawable, public EntityPhysics
{
    public:
        ScenaryElement();
        virtual ~ScenaryElement();

        void update();
        void render();

        virtual void setNode(dwe::Node* n);
        virtual void setPosition(dwe::vec3f p);

    protected:

    private:
        int rotationY;
};

#endif // SCENARYELEMENT_H
