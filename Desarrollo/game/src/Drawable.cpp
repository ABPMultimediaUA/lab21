#include "Drawable.h"

Drawable::Drawable()
{
    //ctor
}

Drawable::~Drawable()
{
    //dtor
}


/////////////////
float* Drawable::getMesh() { return m_mesh; }
void Drawable::setMesh(float* m) { m_mesh = m; }

/////////////////////
fde::vec3f Drawable::getPos() { return m_pos; }
void Drawable::setPos(fde::vec3f p) { m_pos = p; }

/////////////////////
fde::vec3f Drawable::getRot() { return m_rot; }
void Drawable::setRot(fde::vec3f r) { m_rot = r; }
