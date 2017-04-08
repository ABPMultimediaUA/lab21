#include "EntityPhysics.h"
#include "WorldInstance.h"
#include "ScenaryElement.h"

#include "GraphicsEngine.h"

#include <iostream>
#include <cmath>

using namespace std;

///////////////
EntityPhysics::EntityPhysics() :
    m_body(0),
    m_classID(EntityPhysics::no_id)
{
}
EntityPhysics::EntityPhysics(const b2PolygonShape& bShape, b2Body* const bBody) :
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
        /*b2Vec2 vel = m_body->GetLinearVelocity();
        float velX = velocity.x - vel.x;
        float impulseX = m_body->GetMass() * velX;

        float velY = velocity.y - vel.y;
        float impulseY = m_body->GetMass() * velY;

        m_body->ApplyLinearImpulse(b2Vec2(impulseX, impulseY), m_body->GetWorldCenter(), true);*/
    }
    else
        cout << "//////////////////////////////////////\nERROR: No se ha creado m_body con createDynPhyEntity o similar.\n//////////////////////////////////////\n";
}

//////////////////////////
dwe::vec2f EntityPhysics::getVelocity()
{
    b2Vec2 vel = m_body->GetLinearVelocity();
    return dwe::vec2f(vel.x/_ratio, vel.y/_ratio);
}

////////////////////
void EntityPhysics::setForce(dwe::vec2f v)
{
    if (m_body)
        m_body->ApplyForceToCenter(b2Vec2(v.x*_ratio, v.y*_ratio), true); // TODO se tiendrá que pasar la velocidad en m/s por lo que se quitará la multiplicacion
    else
        cout << "//////////////////////////////////////\nERROR: No se ha creado m_body con createDynPhyEntity o similar.\n//////////////////////////////////////\n";
}

////////////////////
void EntityPhysics::createBody(b2BodyType type, const dwe::vec3f& pos, float width, float height, float32 angleDegrees, bool bullet, bool isSensor)
{
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = type;
    bodyDef.position.Set(pos.x*_ratio, pos.z*_ratio);
    bodyDef.angle = -(angleDegrees*M_PI/180);  // Lo pasamos a radianes
    bodyDef.fixedRotation = (type == b2_dynamicBody);
    bodyDef.bullet = bullet;

    m_body = World->createBody(&bodyDef);
    m_body->SetUserData(this);  // Sin esta linea no funcionan los callbacks

    // Define another box shape for our dynamic body.
    m_shape.SetAsBox(width*_ratio/2.f, height*_ratio/2.f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &m_shape;
    fixtureDef.isSensor = isSensor;
    if (type == b2_dynamicBody)
    {
        fixtureDef.density = 1.0f;   // Set the box density to be non-zero, so it will be dynamic.
        fixtureDef.friction = 0.3f;   // Override the default friction.
    }

    // Add the shape to the body.
    m_body->CreateFixture(&fixtureDef);
}
////////////////////
void EntityPhysics::createDoor(const dwe::vec3f& pos, float width, float height, float32 angleDegrees)
{
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(pos.x*_ratio, pos.z*_ratio);
    bodyDef.angle = -(angleDegrees*M_PI/180);  // Lo pasamos a radianes
    bodyDef.fixedRotation = true;

    m_body = World->createBody(&bodyDef);
    m_body->SetUserData(this);  // Sin esta linea no funcionan los callbacks

    // Define another box shape for our dynamic body.
    m_shape.SetAsBox(width*_ratio/2.f, height*_ratio/2.f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &m_shape;
    //fixtureDef.density = 1.0f;   // Set the box density to be non-zero, so it will be dynamic.
    //fixtureDef.friction = 0.0f;   // Override the default friction.

    // Add the shape to the body.
    m_body->CreateFixture(&fixtureDef);
}

////////////////////
void EntityPhysics::createDynamicBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees, bool bullet)
{
    createBody(b2_dynamicBody, pos, width, height, angleDegrees, bullet, false);
}


////////////////////
void EntityPhysics::createStaticBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees)
{
    createBody(b2_staticBody, pos, width, height, angleDegrees, false, false);
}

////////////////////
void EntityPhysics::createSensorBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees)
{
    createBody(b2_staticBody, pos, width, height, angleDegrees, false, true);
}

////////////////////
void EntityPhysics::createJointBody(const dwe::vec3f& pos)
{
    createBody(b2_dynamicBody, pos, 10.0, 10.0, 0, false, false);
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

void EntityPhysics::setPhysicsActive(bool active)
{
    m_body->SetType(b2_dynamicBody);
}
