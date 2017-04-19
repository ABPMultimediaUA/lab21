#ifndef ENTITYPHYSICS_H
#define ENTITYPHYSICS_H

#include "GraphicsEngine.h"
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>

class EntityPhysics
{
    public:
        enum EPClassID { no_id = 0, player_id, playermate_id, projectile_id, wall_id, enemy_id, consumable_id, trigger_id, triggerSound_id, grenadeExplosion_id };

        EntityPhysics();
        virtual ~EntityPhysics();

        EntityPhysics(const b2PolygonShape& bShape, b2Body* const bBody);
        void setEntityPhysics(const b2PolygonShape& bShape, b2Body* const bBody);

        dwe::vec3f getPosEntity();
        void setPosEntity(dwe::vec3f position, float rotation);

        /// \param[in] velocity Velocidad en m/s
        void setVelocity(dwe::vec2f velocity);

        dwe::vec2f getVelocity();

        /// \param[in] f fuerza en m/s
        void setForce(dwe::vec2f f);

        /// \param[in] impulse impulso en m/s
        void setImpulse(dwe::vec2f impulse);

        virtual void onBeginContact(EntityPhysics* otherObject);
        virtual void onEndContact(EntityPhysics* otherObject);

        void setClassID(EPClassID i);
        EPClassID getClassID();

        void setPhysicsActive(bool active);

    protected:
        // Variables para configurar en el constructor sobre el tipo de sólido
        bool        m_fixedRotation;
        bool        m_isSensor;
        bool        m_bullet;
        float32     m_density;
        float32     m_friction;
        float32     m_damping;


        // Se crea el tipo de sólido
        void createCircularBody(const dwe::vec3f& pos, float radius);
        void createDynamicBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees = 0.0);
        void createStaticBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees = 0.0);
        void createKinematicBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees = 0.0);
        void createJointBody(const dwe::vec3f& pos);

    private:
        b2PolygonShape  m_shape;
        b2Body*         m_body;
        EPClassID       m_classID;

        static const float _ratio = 0.035;

        void createBody(b2BodyType type, const dwe::vec3f& pos, float width, float height, float32 angleDegrees);
};

#endif // ENTITYPHYSICS_H
