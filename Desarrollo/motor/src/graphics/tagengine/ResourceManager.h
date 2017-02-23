#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <vector>
#include <string>

#include "Resource.h"

namespace dwe
{
    class ResourceManager
    {
        public:
            ResourceManager();
            ~ResourceManager();

            Resource* getResource(std::string name);

        protected:

        private:
            std::vector<Resource*> m_resources;
    };
}

#endif // RESOURCEMANAGER_H
