#include "tag/Resource.h"

tag::Resource::Resource()
{
    //ctor
}

tag::Resource::~Resource() {}

///////////////////////////
std::string tag::Resource::getName() { return m_name; }
void tag::Resource::setName(std::string name) { m_name = name; }
