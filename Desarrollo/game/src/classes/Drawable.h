#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "GraphicsEngine.h"

class Drawable
{
    public:
        Drawable();
        virtual ~Drawable();

        virtual void update() = 0;
        virtual void render() = 0;

        dwe::vec3f getPosition();
        virtual void setPosition(dwe::vec3f p);

        dwe::vec3f getRotation();
        void setRotation(dwe::vec3f r);

        virtual void setNode(dwe::Node* n);
        dwe::Node* getNode();
        bool hasNode();
        void removeNode();

        void setAnimation(dwe::AnimationType a);
        dwe::AnimationType getAnimation();

        void setActive(bool active);

    protected:

    private:
        dwe::Node*          m_node;
        float*              m_mesh;
        dwe::AnimationType  m_animation;
};

#endif // DRAWABLE_H
