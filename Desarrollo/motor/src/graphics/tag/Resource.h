#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

namespace tag
{
    class Resource
    {
        public:
            Resource();
            virtual ~Resource() = 0;

            std::string getName();
            void setName(std::string name);

        private:
            std::string m_name;
    };
}

#endif // RESOURCE_H
