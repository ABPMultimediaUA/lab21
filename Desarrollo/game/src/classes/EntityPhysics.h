#ifndef ENTITYPHYSICS_H
#define ENTITYPHYSICS_H


#include "DrawableReplica.h"
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>

class EntityPhysics : public dwn::DrawableReplica
{
    public:
        EntityPhysics();
        virtual ~EntityPhysics();

        void update();
        void render();

        EntityPhysics(const b2PolygonShape& bShape, b2Body* const bBody, IrrlichtDevice* const bDevice);
        void setEntityPhysics(const b2PolygonShape& bShape, b2Body* const bBody, IrrlichtDevice* const bDevice);
        void updatePhysics();
        b2Body* getBwBody();

        void createDynPhyEntity(b2World& world, const vector2d<s32>& pos, IrrlichtDevice* const device);



        //tryout
        void createRigidBox(b2World& world, const vector2d<s32>& pos, IrrlichtDevice* const device);
        void createStaticBox(b2World& world, const vector2d<s32>& pos, IrrlichtDevice* const device);

    protected:

    private:
        b2PolygonShape shape;
        b2Body* body;
        IrrlichtDevice* device;

        irr::core::array<EntityPhysics*> bodies; //ARRAY "BODIES"
        EntityPhysics* bwPlayer; //BOX2DPLAYER

};

#endif // ENTITYPHYSICS_H
