#include "EntityPhysics.h"
#include "World.h"
#include <iostream>

using namespace std;

EntityPhysics::EntityPhysics()
{
    m_body = NULL;
    //device = NULL;
    //ctor
}

EntityPhysics::~EntityPhysics()
{
    //dtor
}


EntityPhysics::EntityPhysics(const b2PolygonShape& bShape, b2Body* const bBody){
    m_shape = bShape;
    m_body = bBody;
}


void EntityPhysics::setEntityPhysics(const b2PolygonShape& bShape, b2Body* const bBody){
    m_shape = bShape;
    m_body = bBody;
}


void EntityPhysics::updatePhysics(){
    b2Vec2 position = m_body->GetPosition();
    float32 angle = m_body->GetAngle();

    const b2Mat22 mat(0,1,1,0);
    for(int i=0; i < m_shape.GetVertexCount(); i++){
        //const b2Vec2 vec = body->GetWorldPoint(shape.GetVertex(i));
        const b2Vec2 vec = m_body->GetWorldPoint(b2Mul(mat,m_shape.GetVertex(i)));
        /*
        device->getVideoDriver()->draw2DLine(position2d<s32>(vec.x,vec.y),
        (i+1 != shape.GetVertexCount()) ?
        position2d<s32>(body->GetWorldPoint(b2Mul(mat,shape.GetVertex(i+1))).x, body->GetWorldPoint(b2Mul(mat,shape.GetVertex(i+1))).y):
        position2d<s32>(body->GetWorldPoint(b2Mul(mat,shape.GetVertex(0))).x,body->GetWorldPoint(b2Mul(mat,shape.GetVertex(0))).y),
        SColor(255, 255, 255, 255));
        */

    }
}

b2Body* EntityPhysics::getBwBody(){return m_body;};

///////////////////////
void EntityPhysics::createDynPhyEntity(const dwe::vec3f& pos){
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x, pos.z);
    b2Body* body = WInstance->createBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(10.0f, 10.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    setEntityPhysics(dynamicBox, body);
    //bwPlayer = new EntityPhysics(dynamicBox, body, device);
}

////////////////////////
void EntityPhysics::createRigidBox(const vector2d<s32>& pos){
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.X, pos.Y);
    b2Body* body = WInstance->createBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(10.0f, 10.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    fixtureDef.restitution = 0.0f;
    // Override the default friction.
    fixtureDef.friction = 0.3f;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    /*
    EntityPhysics* bww = new EntityPhysics(dynamicBox, body, device);

    bodies.push_back(bww);
    */
}

//////////////////////
void EntityPhysics::createStaticBox(const vector2d<s32>& pos){
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    //bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.X, pos.Y);
    b2Body* body = WInstance->createBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape staticBox;
    staticBox.SetAsBox(10.0f, 10.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &staticBox;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    /*
    EntityPhysics* bww = new EntityPhysics(staticBox, body, device);

    bodies.push_back(bww);
    */
}
