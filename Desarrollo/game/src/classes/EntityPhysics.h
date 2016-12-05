#ifndef ENTITYPHYSICS_H
#define ENTITYPHYSICS_H


class EntityPhysics
{
    public:
        EntityPhysics();
        virtual ~EntityPhysics();

    protected:

    private:
        b2PolygonShape shape;
        //b2Body* body;
        IrrlichtDevice* device;
};

#endif // ENTITYPHYSICS_H
