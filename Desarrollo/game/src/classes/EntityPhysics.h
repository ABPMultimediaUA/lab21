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
        enum EPClassID { no_id = 0, player_id, projectile_id, wall_id, enemy_id };

        EntityPhysics();
        virtual ~EntityPhysics();

        EntityPhysics(const b2PolygonShape& bShape, b2Body* const bBody);
        void setEntityPhysics(const b2PolygonShape& bShape, b2Body* const bBody);

        dwe::vec3f getPosEntity();
        void setPosEntity(dwe::vec3f position, float rotation);
        void setVelocity(dwe::vec2f v);
        dwe::vec2f getVelocity();

        void setForce(dwe::vec2f v);

        virtual void onBeginContact(EntityPhysics* otherObject);
        virtual void onEndContact(EntityPhysics* otherObject);

        void setClassID(EPClassID i);
        EPClassID getClassID();

    protected:
        // Se crea el tipo de sólido
        void createDynamicBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees = 0.0, bool bullet = false);
        void createStaticBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees);
        void createSensorBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees);
        void createJointBody(const dwe::vec3f& pos);


        void createDoor(const dwe::vec3f& pos, float width, float height, float32 angleDegrees = 0.0);

        void setPhysicsActive(bool active);

    private:
        b2PolygonShape  m_shape;
        b2Body*         m_body;
        EPClassID       m_classID;

        static const float _ratio = 0.035;

        void createBody(b2BodyType type, const dwe::vec3f& pos, float width, float height, float32 angleDegrees, bool bullet, bool isSensor);
};

#endif // ENTITYPHYSICS_H
