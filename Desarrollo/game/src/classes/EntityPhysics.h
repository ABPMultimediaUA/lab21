#ifndef ENTITYPHYSICS_H
#define ENTITYPHYSICS_H

#include "GraphicsEngine.h"
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>

class EntityPhysics
{
    public:
        static const float _ratio = 0.035;

        enum EPClassID
        {
            no_id = 0,
            player_id,
            playermate_id,
            projectile_id,
            wall_id,
            enemy_id,
            consumable_id,
            trigger_id,
            triggerSound_id,
            grenadeExplosion_id ,
            triggerDamage_id,
            triggerVision_id,
            firearm_id
        };

        EntityPhysics();
        virtual ~EntityPhysics();

        EntityPhysics(const b2PolygonShape& bShape, b2Body* const bBody);
        void setEntityPhysics(const b2PolygonShape& bShape, b2Body* const bBody);

        dwe::vec3f getPosEntity();
        void setPosEntity(dwe::vec3f position, float rotation);

        float getRotEntity();

        /// \param[in] velocity Velocidad en m/s
        void setVelocity(dwe::vec2f velocity);

        dwe::vec2f getVelocity();

        /// \param[in] f fuerza en m/s
        void setForce(dwe::vec2f f);

        /// \param[in] impulse impulso en m/s
        void setImpulse(dwe::vec2f impulse);

        void setDensity(float density);

        virtual void onBeginContact(EntityPhysics* otherObject);
        virtual void onEndContact(EntityPhysics* otherObject);

        void setClassID(EPClassID i);
        EPClassID getClassID();

        void setPhysicsActive(bool active);

        void destroyBody();

    protected:
        // Variables para configurar en el constructor sobre el tipo de s�lido
        bool        m_fixedRotation;
        bool        m_isSensor;
        bool        m_bullet;
        float32     m_density;
        float32     m_friction;
        float32     m_damping;
        int m_arc;

        // Se crea el tipo de s�lido
        void createCircularBody(const dwe::vec3f& pos, float radius);
        void createSemiCircleBody(const dwe::vec3f& pos, float radius, float angle, int arc);
        void createDynamicBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees = 0.0, float density = 1.0f);
        void createStaticBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees = 0.0);
        void createKinematicBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees = 0.0);
        void createJointBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees = 0.0);

    private:
        b2PolygonShape  m_shape;
        b2Body*         m_body;
        b2PolygonShape  m_shapeJoint;
        b2Body*         m_bodyJoint;
        EPClassID       m_classID;

        b2RevoluteJoint*    m_revoluteJoint;

        void createBody(b2BodyType type, const dwe::vec3f& pos, float width, float height, float32 angleDegrees, float density = 1.0f);
};

#endif // ENTITYPHYSICS_H
