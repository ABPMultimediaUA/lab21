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


        float* getMesh();
        void setMesh(float* m);

        dwe::vec3f getPosition();
        void setPosition(dwe::vec3f p);

        dwe::vec3f getRotation();
        void setRotation(dwe::vec3f r);

        void setNode(dwe::Node* n);
        /**dwe::Node* getNode();**/
        void removeNode();

        void setAnimation(dwe::AnimationType a);
        dwe::AnimationType getAnimation();

        void setIAnimNode (scene::IAnimatedMeshSceneNode* n);
        scene::IAnimatedMeshSceneNode* getIAnimNode();



    protected:

    private:
        dwe::Node*          m_node;
        float*              m_mesh;
        dwe::AnimationType  m_animation;
        scene::IAnimatedMeshSceneNode* ianim_node;
};

#endif // DRAWABLE_H
