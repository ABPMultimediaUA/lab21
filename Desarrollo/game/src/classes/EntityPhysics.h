#ifndef ENTITYPHYSICS_H
#define ENTITYPHYSICS_H

#include <irrlicht.h>
#include "GraphicsEngine.h"
#include "Drawable.h"
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


        // Se crea el tipo de sólido
        void createDynamicBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees = 0.0, bool bullet = false);
        void createStaticBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees);
        void createSensorBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees);
        void createJointBody(const dwe::vec3f& pos);


        dwe::vec3f getPosEntity();
        void setPosEntity(dwe::vec3f position, float rotation);
        void setVelocity(dwe::vec3f v);

        virtual void onBeginContact(EntityPhysics* otherObject);
        virtual void onEndContact(EntityPhysics* otherObject);

        void setClassID(int i);
        int getClassID();

    protected:

    private:
        b2PolygonShape      m_shape;
        b2Body*             m_body;
        int                 m_classID;

        void createBody(b2BodyType type, const dwe::vec3f& pos, float width, float height, float32 angleDegrees, bool bullet, bool isSensor);
};

#endif // ENTITYPHYSICS_H
