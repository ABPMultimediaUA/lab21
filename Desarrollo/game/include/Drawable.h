#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "FachadeDireEngine.h"

class Drawable
{
    public:
        Drawable();
        virtual ~Drawable();

        virtual void update() = 0;
        virtual void render() = 0;


        float* getMesh();
        void setMesh(float* m);
        fde::vec3f getPos();
        void setPos(fde::vec3f p);
        fde::vec3f getRot();
        void setRot(fde::vec3f r);

    protected:

    private:
        float* m_mesh;
        fde::vec3f m_pos;
        fde::vec3f m_rot;
};

#endif // DRAWABLE_H
