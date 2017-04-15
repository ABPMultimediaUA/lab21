#include "EntityPhysics.h"
#include "WorldInstance.h"
#include "ScenaryElement.h"

#include "GraphicsEngine.h"

#include <iostream>
#include <cmath>

using namespace std;

///////////////
EntityPhysics::EntityPhysics() :
    m_fixedRotation(true), m_isSensor(false), m_bullet(false), m_density(1.0f), m_friction(0.3f),
    m_body(0),
    m_classID(EntityPhysics::no_id)
{
}
EntityPhysics::EntityPhysics(const b2PolygonShape& bShape, b2Body* const bBody) :
    m_fixedRotation(true), m_isSensor(false), m_bullet(false), m_density(1.0f), m_friction(0.3f),
    m_shape(bShape),
    m_body(bBody),
    m_classID(EntityPhysics::no_id)
{
}

///////////////
EntityPhysics::~EntityPhysics()
{
    World->destroyBody(m_body);
}

////////////////////
void EntityPhysics::setEntityPhysics(const b2PolygonShape& bShape, b2Body* const bBody)
{
    m_shape = bShape;
    m_body  = bBody;
}

//////////////////////////
dwe::vec3f EntityPhysics::getPosEntity()
{
    b2Vec2 v = m_body->GetPosition();
    return dwe::vec3f(v.x/_ratio, 0, v.y/_ratio);
}

////////////////////
void EntityPhysics::setPosEntity(dwe::vec3f position, float rotation)
{
    //BOX ROTA EN RADIANES, POR ESO "-(rotation/180)*PI" ... EL SIGNO "-" ES PORQUE EL SISTEMA INTERNO DE ROTACIÓN SON CONTRARIOS ENTRE IRRLICHT Y BOX2D
    m_body->SetTransform(b2Vec2(position.x*_ratio, position.z*_ratio), -(rotation/180*M_PI) );
}

////////////////////
void EntityPhysics::setVelocity(dwe::vec2f velocity)
{
    if (m_body)
    {
        m_body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));  // Se pasa velocidad en m/s
    }
    else
        cout << "//////////////////////////////////////\nERROR: No se ha creado m_body con createDynPhyEntity o similar.\n//////////////////////////////////////\n";
}

//////////////////////////
dwe::vec2f EntityPhysics::getVelocity()
{
    b2Vec2 vel = m_body->GetLinearVelocity();
    return dwe::vec2f(vel.x, vel.y);
}

////////////////////
void EntityPhysics::setForce(dwe::vec2f f)
{
    if (m_body)
        m_body->ApplyForceToCenter(b2Vec2(f.x, f.y), true);
    else
        cout << "//////////////////////////////////////\nERROR: No se ha creado m_body con createDynPhyEntity o similar.\n//////////////////////////////////////\n";
}

////////////////////
void EntityPhysics::setImpulse(dwe::vec2f impulse)
{
    if (m_body)
        m_body->ApplyLinearImpulseToCenter(b2Vec2(impulse.x, impulse.y), true);
    else
        cout << "//////////////////////////////////////\nERROR: No se ha creado m_body con createDynPhyEntity o similar.\n//////////////////////////////////////\n";
}

////////////////////
void EntityPhysics::createBody(b2BodyType type, const dwe::vec3f& pos, float width, float height, float32 angleDegrees)
{
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x*_ratio, pos.z*_ratio);
    bodyDef.type            = type;
    bodyDef.angle           = -(angleDegrees*M_PI/180);  // Lo pasamos a radianes
    bodyDef.fixedRotation   = m_fixedRotation;
    bodyDef.bullet          = m_bullet;

    m_body = World->createBody(&bodyDef);
    m_body->SetUserData(this);  // Sin esta linea no funcionan los callbacks

    // Define another box shape for our dynamic body.
    m_shape.SetAsBox(width*_ratio/2.f, height*_ratio/2.f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape    = &m_shape;
    fixtureDef.isSensor = m_isSensor;
    if (type == b2_dynamicBody)
    {
        fixtureDef.density  = m_density;
        fixtureDef.friction = m_friction;
    }

    // Add the shape to the body.
    m_body->CreateFixture(&fixtureDef);
}

////////////////////
void EntityPhysics::createDynamicBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees)
{
    createBody(b2_dynamicBody, pos, width, height, angleDegrees);
}


////////////////////
void EntityPhysics::createStaticBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees)
{
    createBody(b2_staticBody, pos, width, height, angleDegrees);
}

////////////////////
void EntityPhysics::createKinematicBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees)
{
    createBody(b2_kinematicBody, pos, width, height, angleDegrees);
}

////////////////////
void EntityPhysics::createJointBody(const dwe::vec3f& pos)
{
    createBody(b2_dynamicBody, pos, 10.0, 10.0, 0);
}

////////////////////
void EntityPhysics::onBeginContact(EntityPhysics* otherObject)
{
   // if (otherObject && otherObject->getClassID()==EntityPhysics::player_id) ...
}

////////////////////
void EntityPhysics::onEndContact(EntityPhysics* otherObject)
{

}

////////////////////
void EntityPhysics::setClassID(EPClassID i) { m_classID = i; }
EntityPhysics::EPClassID EntityPhysics::getClassID() { return m_classID; }

////////////////////
void EntityPhysics::setPhysicsActive(bool active)
{
    m_body->SetActive(active);
}
