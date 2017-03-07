#include "tag/ResourceManager.h"

#include "tag/ResourceMesh.h"

tag::ResourceManager::ResourceManager()
{
    //ctor
}

tag::ResourceManager::~ResourceManager()
{
    //dtor
}


tag::Resource* tag::ResourceManager::getResource(std::string name)
{
    // Buscamos si existe el resource
    Resource* res = 0;
    std::vector<Resource*>::iterator it = m_resources.begin();
    while (res == 0 && it != m_resources.end())
    {
        if ((*it)->getName() == name)
            res = *it;
        ++it;
    }

    // Si no existe, la creamos
    if (res == 0)
    {
        // TODO por ahora solo creo recursos malla. Una posible solución : loadResource(name, resource*)
        res = new ResourceMesh();
        res->load(name);
        m_resources.push_back(res);
    }

    return res;
}

