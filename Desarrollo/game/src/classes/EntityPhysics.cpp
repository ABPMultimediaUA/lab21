#include "EntityPhysics.h"
#include "WorldInstance.h"
#include "ScenaryElement.h"

#include "GraphicsEngine.h"

#include <iostream>
#include <cmath>

using namespace std;

EntityPhysics::EntityPhysics()
{
    m_body = NULL;
    m_classID = CLASS_NO_ID;
}

EntityPhysics::~EntityPhysics()
{
    World->destroyBody(m_body);
}

//////////////////////////
dwe::vec3f EntityPhysics::getPosEntity()
{
    b2Vec2 v = m_body->GetPosition();
    return dwe::vec3f(v.x, 0, v.y);
}

////////////////////
void EntityPhysics::setPosEntity(dwe::vec3f position, float rotation)
{
    //BOX ROTA EN RADIANES, POR ESO "-(rotation/180)*PI" ... EL SIGNO "-" ES PORQUE EL SISTEMA INTERNO DE ROTACIÓN SON CONTRARIOS ENTRE IRRLICHT Y BOX2D
    m_body->SetTransform(b2Vec2(position.x, position.z), -(rotation/180*M_PI) );
}

////////////////////
void EntityPhysics::setVelocity(dwe::vec3f v)
{
    if (m_body)
        m_body->SetLinearVelocity(b2Vec2(v.x, v.z));
    else
        cout << "//////////////////////////////////////\nERROR: No se ha creado m_body con createDynPhyEntity o similar.\n//////////////////////////////////////\n";
}

EntityPhysics::EntityPhysics(const b2PolygonShape& bShape, b2Body* const bBody){
    m_shape = bShape;
    m_body = bBody;
}


void EntityPhysics::setEntityPhysics(const b2PolygonShape& bShape, b2Body* const bBody){
    m_shape = bShape;
    m_body = bBody;
}

b2Body* EntityPhysics::getBwBody(){return m_body;};

////////////////////
void EntityPhysics::createBody(b2BodyType type, const dwe::vec3f& pos, float width, float height, float32 angleDegrees, bool bullet, bool isSensor)
{
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = type;
    bodyDef.position.Set(pos.x, pos.z);
   // bodyDef.angle = -(angleDegrees*M_PI/180);  // Lo pasamos a radianes
    bodyDef.fixedRotation = (type == b2_dynamicBody);
    bodyDef.bullet = bullet;

    m_body = World->createBody(&bodyDef);
    m_body->SetUserData(this);  // Sin esta linea no funcionan los callbacks

    // Define another box shape for our dynamic body.
    m_shape.SetAsBox(width/2.f, height/2.f);

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
   // if (otherObject && otherObject->getClassID()==CLASS_PLAYER_ID) ...
}

////////////////////
void EntityPhysics::onEndContact(EntityPhysics* otherObject)
{

}

////////////////////
void EntityPhysics::setClassID(int i) { m_classID = i; }
int EntityPhysics::getClassID() { return m_classID; }

