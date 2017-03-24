#ifndef TAG_RESOURCEMANAGER_H
#define TAG_RESOURCEMANAGER_H

#include <vector>
#include <string>

#include "Resource.h"

namespace tag
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

#endif // TAG_RESOURCEMANAGER_H
