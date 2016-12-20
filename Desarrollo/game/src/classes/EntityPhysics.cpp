#include "EntityPhysics.h"
#include "WorldInstance.h"
#include "ScenaryElement.h"
#include <iostream>

using namespace std;

EntityPhysics::EntityPhysics()
{
    m_body = NULL;
    m_classID = CLASS_NO_ID;
/*
    switch(k)
    {
    case eDynPhy:
        createDynPhyEntity(pos);
        break;
    case eRigidBox:
        createRigidBox(pos);
        break;
    case eStaticBox:
        createStaticBox(pos, halfWidth, halfHeight);
        break;
    }
    */
}

EntityPhysics::~EntityPhysics()
{
    //dtor
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
    m_body->SetTransform(b2Vec2(position.x, position.z), rotation);
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


void EntityPhysics::updatePhysics()
{
//    Drawable::setPosition(dwe::vec3f(getBwBody()->GetPosition().x, getPosition().y, getBwBody()->GetPosition().y));
    /*
    b2Vec2 position = m_body->GetPosition();
    float32 angle = m_body->GetAngle();

    const b2Mat22 mat(0,1,1,0);
    for(int i=0; i < m_shape.GetVertexCount(); i++){
        //const b2Vec2 vec = body->GetWorldPoint(shape.GetVertex(i));
        const b2Vec2 vec = m_body->GetWorldPoint(b2Mul(mat,m_shape.GetVertex(i)));
        device->getVideoDriver()->draw2DLine(position2d<s32>(vec.x,vec.y),
        (i+1 != shape.GetVertexCount()) ?
        position2d<s32>(body->GetWorldPoint(b2Mul(mat,shape.GetVertex(i+1))).x, body->GetWorldPoint(b2Mul(mat,shape.GetVertex(i+1))).y):
        position2d<s32>(body->GetWorldPoint(b2Mul(mat,shape.GetVertex(0))).x,body->GetWorldPoint(b2Mul(mat,shape.GetVertex(0))).y),
        SColor(255, 255, 255, 255));

    }*/
}

b2Body* EntityPhysics::getBwBody(){return m_body;};

////////////////////
void EntityPhysics::createDynamicBody(const dwe::vec3f& pos){
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x, pos.z);

    m_body = World->createBody(&bodyDef);
    m_body->SetUserData(this);  // Sin esta linea no funcionan los callbacks

    // Define another box shape for our dynamic body.
    m_shape.SetAsBox(10.0f, 10.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &m_shape;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;

    // Add the shape to the body.
    m_body->CreateFixture(&fixtureDef);
}


//////////////////////
void EntityPhysics::createStaticBody(const dwe::vec3f& pos, float width, float height){
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(pos.x, pos.z);

    m_body = World->createBody(&bodyDef);
    m_body->SetUserData(this);  // Sin esta linea no funcionan los callbacks

    // Define another box shape for our dynamic body.
    m_shape.SetAsBox(width/2.f, height/2.f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &m_shape;

    // Add the shape to the body.
    m_body->CreateFixture(&fixtureDef);
}

////////////////////
void EntityPhysics::onBeginContact(EntityPhysics* otherObject)
{
   // if (otherObject && otherObject->getClassID()==CLASS_PLAYER_ID) ...
}

////////////////////
void EntityPhysics::onEndContact()
{

}

////////////////////
void EntityPhysics::setClassID(int i) { m_classID = i; }
int EntityPhysics::getClassID() { return m_classID; }

