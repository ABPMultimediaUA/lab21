#ifndef ENTITYPHYSICS_H
#define ENTITYPHYSICS_H

#include "GraphicsEngine.h"
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>

class EntityPhysics
{
    public:
        enum EPClassID { no_id = 0, player_id, playermate_id, projectile_id, wall_id, enemy_id };

        EntityPhysics();
        virtual ~EntityPhysics();

        EntityPhysics(const b2PolygonShape& bShape, b2Body* const bBody);
        void setEntityPhysics(const b2PolygonShape& bShape, b2Body* const bBody);

        dwe::vec3f getPosEntity();
        void setPosEntity(dwe::vec3f position, float rotation);

        /// \param[in] velocity Velocidad en m/s
        void setVelocity(dwe::vec2f velocity);

        dwe::vec2f getVelocity();

        void setForce(dwe::vec2f v);

        virtual void onBeginContact(EntityPhysics* otherObject);
        virtual void onEndContact(EntityPhysics* otherObject);

        void setClassID(EPClassID i);
        EPClassID getClassID();

        void setPhysicsActive(bool active);

    protected:
        // Se crea el tipo de sólido
        void createDynamicBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees = 0.0, bool bullet = false);
        void createStaticBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees = 0.0);
        void createDynamicSensorBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees = 0.0);
        void createStaticSensorBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees = 0.0);
        void createJointBody(const dwe::vec3f& pos);


        void createDoor(const dwe::vec3f& pos, float width, float height, float32 angleDegrees = 0.0);


    private:
        b2PolygonShape  m_shape;
        b2Body*         m_body;
        EPClassID       m_classID;

        static const float _ratio = 0.035;

        void createBody(b2BodyType type, const dwe::vec3f& pos, float width, float height, float32 angleDegrees, bool bullet, bool isSensor);
};

#endif // ENTITYPHYSICS_H
