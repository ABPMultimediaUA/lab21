#include "tag/ResourceManager.h"

#include <iostream>

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

    if (res == 0)
    {
        // TODO por ahora solo creo recursos malla
        res = new ResourceMesh();
        static_cast<ResourceMesh*>(res)->load(name);  // TODO para quitar el static_cast, hacer que TResource tenga un load virtual puro
        m_resources.push_back(res);

        std::cout << "creamos nueva: " << name << "\n";
    }
    else
        std::cout << "usamos previamente: " << name << "\n";

    return res;
}

