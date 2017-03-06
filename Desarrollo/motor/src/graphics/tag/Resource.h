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

            /// \brief Función que cargará el recurso que sea desde el fichero.
            /// \details Debe estar implementada en las clases heredadas.
            virtual void load(std::string fileName) = 0;

            std::string getName();
            void setName(std::string name);

        private:
            std::string m_name;
    };
}

#endif // RESOURCE_H
