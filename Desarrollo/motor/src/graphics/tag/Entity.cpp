#include "tag/Entity.h"

glm::mat4 tag::Entity::MVmatrix;
std::stack<glm::mat4> tag::Entity::TStack;

tag::Entity::Entity()
{
    //ctor
}

tag::Entity::~Entity()
{
    //dtor
}

