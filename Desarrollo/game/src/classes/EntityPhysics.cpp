#include "EntityPhysics.h"
#include <iostream>
using namespace std;

EntityPhysics::EntityPhysics()
{
    body = NULL;
    device = NULL;
    //ctor
}

EntityPhysics::~EntityPhysics()
{
    //dtor
}



EntityPhysics::EntityPhysics(const b2PolygonShape& bShape, b2Body* const bBody, IrrlichtDevice* const bDevice){
    shape = bShape;
    body = bBody;
    device = bDevice;
}


void EntityPhysics::setEntityPhysics(const b2PolygonShape& bShape, b2Body* const bBody, IrrlichtDevice* const bDevice){
    shape = bShape;
    body = bBody;
    device = bDevice;
}


void EntityPhysics::updatePhysics(){
    b2Vec2 position = body->GetPosition();
    float32 angle = body->GetAngle();

    const b2Mat22 mat(0,1,1,0);
    for(int i=0; i < shape.GetVertexCount(); i++){
        //const b2Vec2 vec = body->GetWorldPoint(shape.GetVertex(i));
        const b2Vec2 vec = body->GetWorldPoint(b2Mul(mat,shape.GetVertex(i)));

        device->getVideoDriver()->draw2DLine(position2d<s32>(vec.x,vec.y),
        (i+1 != shape.GetVertexCount()) ?
        position2d<s32>(body->GetWorldPoint(b2Mul(mat,shape.GetVertex(i+1))).x, body->GetWorldPoint(b2Mul(mat,shape.GetVertex(i+1))).y):
        position2d<s32>(body->GetWorldPoint(b2Mul(mat,shape.GetVertex(0))).x,body->GetWorldPoint(b2Mul(mat,shape.GetVertex(0))).y),
        SColor(255, 255, 255, 255));

    }
}

b2Body* EntityPhysics::getBwBody(){return body;};

///////////////////////
void EntityPhysics::createDynPhyEntity(b2World& world, const vector2d<s32>& pos, IrrlichtDevice* const device){
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.X, pos.Y);
    b2Body* body = world.CreateBody(&bodyDef);

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

    setEntityPhysics(dynamicBox, body, device);
    //bwPlayer = new EntityPhysics(dynamicBox, body, device);
}

////////////////////////
void EntityPhysics::createRigidBox(b2World& world, const vector2d<s32>& pos, IrrlichtDevice* const device){
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.X, pos.Y);
    b2Body* body = world.CreateBody(&bodyDef);

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

    EntityPhysics* bww = new EntityPhysics(dynamicBox, body, device);

    bodies.push_back(bww);
}

//////////////////////
void EntityPhysics::createStaticBox(b2World& world, const vector2d<s32>& pos, IrrlichtDevice* const device){
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    //bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.X, pos.Y);
    b2Body* body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape staticBox;
    staticBox.SetAsBox(10.0f, 10.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &staticBox;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    EntityPhysics* bww = new EntityPhysics(staticBox, body, device);

    bodies.push_back(bww);
}
