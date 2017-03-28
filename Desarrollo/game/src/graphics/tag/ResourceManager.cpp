#include "tag/ResourceManager.h"

#include <stdexcept>

#include "tag/ResourceMesh.h"
#include "tag/ResourceTexture.h"

tag::ResourceManager::ResourceManager()
{
    m_resourceKinds["obj"] = createResourceMesh;
    m_resourceKinds["md2"] = createResourceMesh;
    m_resourceKinds["bmp"] = createResourceTexture;
}

tag::ResourceManager::~ResourceManager()
{
    //dtor
}

tag::Resource* tag::ResourceManager::createResourceMesh()
{
    return (new ResourceMesh());
}

tag::Resource* tag::ResourceManager::createResourceTexture()
{
    return (new ResourceTexture());
}

tag::Resource* tag::ResourceManager::searchForResource(std::string name)
{
    Resource* res = 0;
    std::vector<Resource*>::iterator it = m_resources.begin();
    while (res == 0 && it != m_resources.end())
    {
        if ((*it)->getName() == name)
            res = *it;
        ++it;
    }
    return res;
}

tag::Resource* tag::ResourceManager::createResource(std::string name)
{
    ResourceKinds::iterator it;
    it = m_resourceKinds.find(name.substr(name.find_last_of(".") + 1));
    if (it == m_resourceKinds.end())  // Error, extensión no está en m_resourceKinds
        throw std::runtime_error("ResourceManager no puede localizar la extension. No esta entre las soportadas.");

    Resource* res = (this->*it->second)();

    res->load(name);
    m_resources.push_back(res);

    return res;
}

tag::Resource* tag::ResourceManager::getResource(std::string name)
{
    // Buscamos si existe el resource
    Resource* res = searchForResource(name);

    // Si no existe, la creamos
    if (res == 0)
        res = createResource(name);

    return res;
}

