#ifndef ENTITYPHYSICS_H
#define ENTITYPHYSICS_H

#include "GraphicsEngine.h"
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>

class EntityPhysics
{
    public:
        EntityPhysics();
        virtual ~EntityPhysics();

        EntityPhysics(const b2PolygonShape& bShape, b2Body* const bBody);
        void setEntityPhysics(const b2PolygonShape& bShape, b2Body* const bBody);
        b2Body* getBwBody();

        void createDynPhyEntity(const dwe::vec3f& pos);



        //tryout
        void createRigidBox(const vector2d<s32>& pos);
        void createStaticBox(const vector2d<s32>& pos);

    protected:

    private:
        void updatePhysics();  // Por ahora no sirve de nada
        b2PolygonShape      m_shape;
        b2Body*             m_body;
        IrrlichtDevice*     m_device;

        irr::core::array<EntityPhysics*>    m_bodies; //ARRAY "BODIES"
        EntityPhysics*                      m_bwPlayer; //BOX2DPLAYER

};

#endif // ENTITYPHYSICS_H
