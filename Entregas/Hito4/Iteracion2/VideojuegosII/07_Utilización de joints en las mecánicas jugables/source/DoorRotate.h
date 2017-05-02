#ifndef DOORROTATE_H
#define DOORROTATE_H

#include "Entity.h"

class DoorRotate: public Entity
{
    public:
        DoorRotate(int f, bool a);
        virtual ~DoorRotate();
        void setActive();
        void setInactive(); // DEMO
        bool getActive();
        virtual void render();
        virtual void update();

        virtual void setNode(dwe::Node* n);
        virtual void setPosition(dwe::vec3f p);

    protected:

    private:
        float x,y,z;
        int facing; // 0 1 2 3
        bool active;
};

#endif // DOORROTATE_H
