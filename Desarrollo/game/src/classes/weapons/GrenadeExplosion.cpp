#include "GrenadeExplosion.h"
#include "AudioEngine.h"



GrenadeExplosion::GrenadeExplosion()
{
    //ctor
    m_isSensor = true;
    setClassID(EntityPhysics::grenadeExplosion_id);
}


GrenadeExplosion::~GrenadeExplosion()
{
    //dtor
}

void GrenadeExplosion::render(){};

void GrenadeExplosion::update()
{
}

void GrenadeExplosion::setNode(dwe::Node* n)
{
    Drawable::setNode(n);

    dwe::vec3f box = n->getBoundingBox();
    //createKinematicBody(getPosition(), box.x, box.z, getRotation().y);
    createCircularBody(getPosition(), box.x/2.0);
    AEInstance->Play2D("media/Sounds/Granada.wav");
}

void GrenadeExplosion::onBeginContact(EntityPhysics* otherObject)
{
//    m_collides = (otherObject && otherObject->getClassID()!=EntityPhysics::player_id);
}
