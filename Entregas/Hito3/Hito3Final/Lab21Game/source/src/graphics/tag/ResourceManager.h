#ifndef TAG_RESOURCEMANAGER_H
#define TAG_RESOURCEMANAGER_H

#include <vector>
#include <string>
#include <map>

#include "Resource.h"

namespace tag
{
    class ResourceManager
    {
        typedef Resource* (ResourceManager::*FunctionPointer)();
        typedef std::map<std::string, FunctionPointer> ResourceKinds;
        public:
            ResourceManager();
            ~ResourceManager();

            Resource* getResource(std::string name);

        protected:

        private:
            std::vector<Resource*>  m_resources;
            ResourceKinds           m_resourceKinds;

            Resource* createResourceMesh();
            Resource* createResourceTexture();
            Resource* searchForResource(std::string name);
            Resource* createResource(std::string name);
    };
}

#endif // TAG_RESOURCEMANAGER_H
