#include "DoorRotate.h"
#include "NetGame.h"

DoorRotate::DoorRotate(int f, bool a)
{
    x = 0;  y = 0;  z = 0;
    facing = f;
    active = a;
    m_fixedRotation = false;
}

DoorRotate::~DoorRotate()
{
}

void DoorRotate::setActive()  {   active=true;      }
void DoorRotate::setInactive()  {   active=false;      }
bool DoorRotate::getActive()  {   return active;    }


void DoorRotate::update()
{
    dwe::vec3f rot = getRotation();
    dwe::vec3f pos = getPosEntity();
    Drawable::setRotation(dwe::vec3f(rot.x, getRotEntity(), rot.z));
    Drawable::setPosition(dwe::vec3f(pos.x, getPosition().y, pos.z));
}

void DoorRotate::render()
{
    // dibujar nodo
}

void DoorRotate::setNode(dwe::Node* n)
{
    Drawable::setNode(n);

    dwe::vec3f s = n->getBoundingBox();

    float rotation=0;
    if(facing==1 ||facing ==3)
        rotation=90;
    createJointBody(getPosition(), s.x, s.z, rotation);
    setRotation(dwe::vec3f(0, rotation, 0));
}

void DoorRotate::setPosition(dwe::vec3f p)
{
    DrawablePhysics::setPosition(p);
}
