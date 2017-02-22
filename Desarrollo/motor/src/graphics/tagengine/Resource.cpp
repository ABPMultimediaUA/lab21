#include "Resource.h"

dwe::Resource::Resource()
{
    //ctor
}

dwe::Resource::~Resource() {}

///////////////////////////
std::string dwe::Resource::getName() { return m_name; }
void dwe::Resource::setName(std::string name) { m_name = name; }
