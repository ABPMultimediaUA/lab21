#include "tag/Entity.h"

glm::mat4 tag::Entity::modelMatrix;
glm::mat4 tag::Entity::viewMatrix;
glm::mat4 tag::Entity::projectionMatrix;
std::stack<glm::mat4> tag::Entity::TStack;
tag::ResourceManager tag::Entity::resourceManager;

tag::Entity::Entity()
{
    //ctor
}

tag::Entity::~Entity()
{
    //dtor
}

