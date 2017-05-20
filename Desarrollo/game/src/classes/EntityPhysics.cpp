#include "EntityPhysics.h"
#include "WorldInstance.h"

#include <iostream>
#include <cmath>

using namespace std;

///////////////
EntityPhysics::EntityPhysics() :
    m_fixedRotation(true), m_isSensor(false), m_bullet(false), m_density(1.0f), m_friction(0.3f), m_damping(0.0f),
    m_body(0),
    m_bodyJoint(0),
    m_classID(EntityPhysics::no_id),
    m_revoluteJoint(0)
{
}
EntityPhysics::EntityPhysics(const b2PolygonShape& bShape, b2Body* const bBody) :
    m_fixedRotation(true), m_isSensor(false), m_bullet(false), m_density(1.0f), m_friction(0.3f), m_damping(0.0f),
    m_shape(bShape), m_body(bBody),
    m_bodyJoint(0),
    m_classID(EntityPhysics::no_id),
    m_revoluteJoint(0)
{
}

///////////////
EntityPhysics::~EntityPhysics()
{
    if (m_revoluteJoint)
    {
        World->destroyJoint(m_revoluteJoint);
        m_revoluteJoint = 0;
    }
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

//////////////////////////
float EntityPhysics::getRotEntity()
{
    return (- m_body->GetAngle()*180/M_PI);
}

////////////////////
void EntityPhysics::setPosEntity(dwe::vec3f position, float rotation)
{
    //BOX ROTA EN RADIANES, POR ESO "-(rotation/180)*PI" ... EL SIGNO "-" ES PORQUE EL SISTEMA INTERNO DE ROTACIÓN SON CONTRARIOS ENTRE IRRLICHT Y BOX2D
    m_body->SetTransform(b2Vec2(position.x*_ratio, position.z*_ratio), -(rotation/180*M_PI) );
    if (m_bodyJoint)
        m_bodyJoint->SetTransform(b2Vec2(position.x*_ratio, position.z*_ratio), -(rotation/180*M_PI) );
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
void EntityPhysics::createBody(b2BodyType type, const dwe::vec3f& pos, float width, float height, float32 angleDegrees, float density)
{
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x*_ratio, pos.z*_ratio);
    bodyDef.type            = type;
    bodyDef.angle           = -(angleDegrees*M_PI/180);  // Lo pasamos a radianes
    bodyDef.fixedRotation   = m_fixedRotation;
    bodyDef.bullet          = m_bullet;
    bodyDef.angularDamping  = m_damping;
    bodyDef.linearDamping   = m_damping;

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
        fixtureDef.density  = density;
        fixtureDef.friction = m_friction;
    }

    // Add the shape to the body.
    m_body->CreateFixture(&fixtureDef);
}

void EntityPhysics::createCircularBody(const dwe::vec3f& pos, float radius)
{
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x*_ratio, pos.z*_ratio);
    bodyDef.type            = b2_kinematicBody;
    bodyDef.angle           = 0;  // Lo pasamos a radianes
    bodyDef.fixedRotation   = m_fixedRotation;
    bodyDef.bullet          = m_bullet;
    bodyDef.angularDamping  = m_damping;
    bodyDef.linearDamping   = m_damping;

    m_body = World->createBody(&bodyDef);
    m_body->SetUserData(this);  // Sin esta linea no funcionan los callbacks

    // Define a circle shape for our dynamic body.
    b2CircleShape circle_shape;
    circle_shape.m_p.Set(0,0);
    circle_shape.m_radius = radius;

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape    = &circle_shape;
    fixtureDef.isSensor = m_isSensor;
    if (bodyDef.type == b2_dynamicBody)
    {
        fixtureDef.density  = m_density;
        fixtureDef.friction = m_friction;
    }

    // Add the shape to the body.
    m_body->CreateFixture(&fixtureDef);
}

void EntityPhysics::createSemiCircleBody(const dwe::vec3f& pos, float radius, float angle, int arc)
{
    m_arc = arc;
    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x*_ratio, pos.z*_ratio);
    bodyDef.type            = b2_kinematicBody;
    bodyDef.angle           = -(angle+m_arc/2)*M_PI/180;  // Lo pasamos a radianes
    bodyDef.fixedRotation   = m_fixedRotation;
    bodyDef.bullet          = m_bullet;
    bodyDef.angularDamping  = m_damping;
    bodyDef.linearDamping   = m_damping;

    m_body = World->createBody(&bodyDef);
    m_body->SetUserData(this);  // Sin esta linea no funcionan los callbacks

    b2Vec2 vertices[8];
    vertices[0].Set(0,0);
    for (int i = 0; i < 7; i++) {
        angle = i / 6.0 * m_arc * M_PI/180;
        vertices[i+1].Set( radius * cosf(angle), radius * sinf(angle) );
    }
    m_shape.Set(vertices, 8);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &m_shape;
    fixtureDef.isSensor = m_isSensor;
    if (bodyDef.type == b2_dynamicBody)
    {
        fixtureDef.density  = m_density;
        fixtureDef.friction = m_friction;
    }

    m_body->CreateFixture(&fixtureDef);
}

////////////////////
void EntityPhysics::createDynamicBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees, float32 density)
{
    createBody(b2_dynamicBody, pos, width, height, angleDegrees, density);
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
void EntityPhysics::createJointBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees)
{
    createBody(b2_dynamicBody, pos, width, height, angleDegrees);

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x*_ratio, pos.z*_ratio);
    bodyDef.type            = b2_kinematicBody;
    bodyDef.angle           = -(angleDegrees*M_PI/180);  // Lo pasamos a radianes
    bodyDef.fixedRotation   = true;
    bodyDef.angularDamping  = m_damping;
    bodyDef.linearDamping   = m_damping;

    m_bodyJoint = World->createBody(&bodyDef);
    m_bodyJoint->SetUserData(this);  // Sin esta linea no funcionan los callbacks

    // Define another box shape for our dynamic body.
    m_shapeJoint.SetAsBox(0.1, 0.1);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape    = &m_shapeJoint;
    fixtureDef.isSensor = true;

    // Add the shape to the body.
    m_bodyJoint->CreateFixture(&fixtureDef);

    // Prismatic joint
    b2RevoluteJointDef jointDef;
    if (angleDegrees == 90)
        jointDef.Initialize(m_body, m_bodyJoint, m_body->GetWorldPoint(b2Vec2(0,-(height*_ratio/2.0))));
    else
        jointDef.Initialize(m_body, m_bodyJoint, m_body->GetWorldPoint(b2Vec2(-(width*_ratio/2.0),0)));
    jointDef.maxMotorTorque = 10.0;
    jointDef.motorSpeed = 0.0;
    jointDef.enableMotor = true;

    m_revoluteJoint = (b2RevoluteJoint*)World->createJoint(&jointDef);
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
